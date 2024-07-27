import java.io.File
import java.util.PriorityQueue
import java.util.Scanner
import java.util.Stack

class Station {
    val id_map = HashMap<Char, Char>()
    val nearby = ArrayList<Station>()
}

data class State (
    val cost: Int,
    val station: Station,
    val prev: Station?,
    val line: HashSet<Char>
): Comparable<State> {
    override fun compareTo(other: State): Int {
        return cost.compareTo(other.cost)
    }
}

fun get_station (id_ls: ArrayList<String>, station_map: HashMap<String, Station>): Station? {
    for (id in id_ls) {
       if (station_map.containsKey(id)) {
           return station_map[id]!!
       }
    }
    return null
}

fun build_graph (sc: Scanner): HashMap<String, Station> {
    val station_map = HashMap<String, Station>()

    val n = sc.nextInt()
    sc.nextLine()
    for (i in 1..n) {
        val line = sc.nextLine()
        val line_nm = line[0]

        var j = 2
        var prev_station: Station? = null
        while (j < line.length) {
            // get all names of the station
            val station_id_ls = ArrayList<String>(listOf("$line_nm${line[j]}"))
            j++
            while (j < line.length && line[j] == '=') {
                station_id_ls.add("${line[j + 1]}${line[j + 2]}")
                j += 3
            }

            // set the line of the station
            val station = get_station(station_id_ls, station_map)?.let { it } ?: run { Station() }
            for (id in station_id_ls) {
                station.id_map[id[0]] = id[1]
                if (!station_map.containsKey(id)) {
                    station_map[id] = station
                }
            }

            // connect with prev station
            prev_station?.let {
                it.nearby.add(station)
                station.nearby.add(it)
            }
            prev_station = station
        }
    }

    return station_map
}

fun common_line (a: MutableSet<Char>, b: MutableSet<Char>): HashSet<Char> {
    val res: HashSet<Char> = HashSet(a)
    res.retainAll(b)
    return res
}

fun solve (srt: Station, dst: Station, srt_line: Char) {
    val q: PriorityQueue<State> = PriorityQueue()
    val state_map: HashMap<Station, State> = HashMap()

    q.offer(State(0, srt, null, HashSet(listOf(srt_line))))

    while (!q.isEmpty()) {
        val state = q.poll()!!
        if (state_map.contains(state.station)) {
            continue
        }
        state_map[state.station] = state

        if (state.station == dst) {
            break
        }

        for (next in state.station.nearby) {
            val station_common_line = common_line(state.station.id_map.keys, next.id_map.keys)
            val state_common_line = common_line(state.line, station_common_line)

            if (state_common_line.isEmpty()) {
                q.offer(State(state.cost + 4, next, state.station, station_common_line))
            } else {
                q.offer(State(state.cost + 1, next, state.station, state_common_line))
            }
        }
    }

    // build trace back stack
    val state_stack = Stack<State>()
    val line_stack = Stack<Char>()
    var station: Station? = dst
    while (station != null) {
        val state = state_map[station]!!
        state_stack.add(state)
        line_stack.add(
            if (line_stack.isEmpty()) {
                state.line.first()
            }
            else {
                val next_line = line_stack.peek()
                if (state.line.contains(next_line)) {
                    next_line
                } else {
                    state.line.first()
                }
            }
        )
        station = state.prev
    }

    // trace back
    print("${state_map[dst]!!.cost.toString().padStart(3)}: ${srt_line}")
    var prev_station: Station? = null
    var prev_line: Char = srt_line
    while (state_stack.isNotEmpty()) {
        val state = state_stack.pop()
        val line = line_stack.pop()
        if (prev_line == line) {
            print("${state.station.id_map[line]}")
        } else {
            print("=${line}${prev_station!!.id_map[line]}${state.station.id_map[line]}")
            prev_line = line
        }
        prev_station = state.station
    }
    println()
}

fun main () {
    val sc = Scanner(File("input.txt"))
    val station_map = build_graph(sc)

    while (true) {
        val line = sc.nextLine()
        if (line == "#") {
            break
        }
        solve(
            station_map["${line[0]}${line[1]}"]!!,
            station_map["${line[2]}${line[3]}"]!!,
            line[0]
        )
    }
}
