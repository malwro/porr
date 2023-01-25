package edu.pw.porr

import org.apache.spark.sql.SparkSession

import java.nio.file.{Files, Paths, StandardOpenOption}
import scala.concurrent.duration.NANOSECONDS
import scala.jdk.CollectionConverters._

object Main extends App {
  //Definicja przypadków dla których eksperymenty zostaną przeprowadzone
  val testNames = Seq("10_multiplied_text", "50_multiplied_text", "150_multiplied_text")
  val numberOfCores = Seq(1, 2, 4, 6, 8, 10, 12, 16, 20)
  val partitions = Seq(32)
  val samples = 2

  //Uruchomienie testów
  testNames.foreach { testName =>
    val results = List.fill(samples)(numberOfCores).flatten.flatMap { cores =>
      partitions.map(numberOfPartitions => (cores, numberOfPartitions, runTest(testName, cores, numberOfPartitions)))

    }

    //Zapisanie wyników testów do pliku
    Files.write(
      Paths.get(s"./result/${testName}_result.txt"),
      results.map(_.toString()).asJava,
      StandardOpenOption.CREATE,
      StandardOpenOption.TRUNCATE_EXISTING
    )
  }

  //Funkcja przeprowadzająca test
  def runTest(testName: String, numberOfThreads: Int, numberOfPartitions: Int) = {
    //Uruchomienie klastra Spark w trybie standalone korzystającego z zadanej liczby rdzeni
    val spark = SparkSession.builder()
      .master(s"local[$numberOfThreads]")
      .appName("PORR")
      .getOrCreate()


    //Początek pomiaru czasu
    val start = System.nanoTime()
    val rdd = spark.sparkContext//pobranie kontekstu aplikacji klienta Spark
      .textFile(s"./txt_files_for_tests/$testName.txt", numberOfPartitions)//wczytanie pliku z zadaną liczbą partycji
      .flatMap(_.split("[ \n\t]"))//podział pliku na słowa

    val result = rdd.countByValue()//zliczenie wystąpień słów
    //Zapisanie wyniku zliczania do pliku
    Files.write(Paths.get(s"./result/dump.txt"),
      result.map(_.toString()).asJava,
      StandardOpenOption.CREATE,
      StandardOpenOption.TRUNCATE_EXISTING)
    val end = System.nanoTime()//zakończenie poamiru czasu

    spark.close()//zakmnięcie klastra
    NANOSECONDS.toMillis(end - start)//zwrócenie czasu trwania obliczeń
  }

}