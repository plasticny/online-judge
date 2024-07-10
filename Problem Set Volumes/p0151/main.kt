import java.io.File
import java.util.LinkedList
import java.util.Scanner
import java.util.Queue

fun solve (n: Int) : Int {
  var m = 1

  while (true) {
    val q : Queue<Int> = LinkedList()
    for (i in 1..n) {
      q.add(i)
    }

    while (true) {
      q.poll()
      if (q.size == 1) {
        break
      }

      var mm = m % q.size
      if (mm == 0) {
        mm = m
      }
      for (i in 0 until mm - 1) {
        q.add(q.poll())
      }
    }

    if (q.poll() == 13) {
      break
    }
    m++
  }

  return m
}

fun main(args: Array<String>) {
  val sc = Scanner(File("input.txt"))

  while (sc.hasNext()) {
    val n = sc.nextInt()
    if (n == 0) {
      break
    }
    println(solve(n))
  }
}
