package edu.pw.porr

import org.apache.spark.sql.SparkSession

import java.nio.file.{Files, Paths, StandardOpenOption}
import scala.concurrent.duration.NANOSECONDS
import scala.jdk.CollectionConverters._

object Main extends App {

  val testNames = Seq("10_multiplied_text", "50_multiplied_text", "150_multiplied_text")
  val numberOfCores = Seq(1,2,4,6,8,10,12, 20)
  val samples = 10

  testNames.foreach { testName =>
    val results = List.fill(samples)(numberOfCores).flatten.map { cores =>
      (cores, runTest(testName, cores))
    }
    Files.write(Paths.get(s"./result/${testName}_result.txt"), results.map(_.toString()).asJava, StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING)
  }

  def runTest(testName: String, numberOfThreads: Int) = {
    val spark = SparkSession.builder()
      .master(s"local[$numberOfThreads]")
      .appName("PORR")
      .getOrCreate()

    val start = System.nanoTime()
    spark.sparkContext
      .textFile(s"./txt_files_for_tests/$testName.txt")
      .flatMap(_.split("[ \n\t]"))
      .countByValue()
    val end = System.nanoTime()

    spark.close()
    NANOSECONDS.toMillis(end - start)
  }

}

/**
 * 10_multiplied_text
 * local[1] - Time taken: 4642 ms
 * local[3] - Time taken: 3354 ms
 * local[16] - Time taken: 3363 ms
 *
 * 150_multiplied_text
 * local[1] - Time taken: 42944 ms
 * local[16] - Time taken: 9161 ms
 * local[160] - Time taken: 10466 ms
 */