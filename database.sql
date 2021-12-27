-- MySQL dump 10.13  Distrib 8.0.27, for Linux (x86_64)
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	8.0.27-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `reserv`
--

DROP TABLE IF EXISTS `reserv`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reserv` (
  `reserv_id` int NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `theme` varchar(100) NOT NULL,
  `entertainment` varchar(100) NOT NULL,
  `day` varchar(4) NOT NULL,
  `month` varchar(4) NOT NULL,
  `food` varchar(100) NOT NULL,
  `music` varchar(100) NOT NULL,
  PRIMARY KEY (`reserv_id`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reserv`
--

LOCK TABLES `reserv` WRITE;
/*!40000 ALTER TABLE `reserv` DISABLE KEYS */;
INSERT INTO `reserv` VALUES (7,'monto','wedding','Dance','4','1','pizza','pop'),(9,'Linux','Islam','Arabic dance','13','11','Kebab','Ethnic'),(11,'Linux','Lap','Dap','1','9','Cap','Map'),(13,'gap','dancenight','dancday','3','3','pizza','pop,jaz '),(18,'demon','Party','Dancers','8','8','Pizza Apple','Pop EDM'),(19,'demon','Wedding','Dancers','8','12','Cake','Pop EDM'),(20,'demon','Wedding','Dancers','23','7','Cake','Pop EDM'),(23,'demona','weding','weding day','5','3','cake,pizza','pop,jazz'),(24,'demon','Wedding','Marriage','14','7','Pizza, barbeue','Pop, Folk');
/*!40000 ALTER TABLE `reserv` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `password` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'jack','pass2'),(2,'Linux','Lore'),(3,'atto','man89'),(4,'Morning','bre90'),(5,'demona','333333'),(6,'demonbeka1s2d3','a1s2d3'),(7,'losp','assgreeny_20'),(8,'demona','gola'),(9,'oplunassgreeny_20','assgreeny_20'),(10,'losp','assgreeny_20'),(11,'losp','assgreeny_20'),(12,'losp','losp18'),(13,'demon','a1s2d3'),(14,'Tanya','150818'),(15,'demon','a1s2d3'),(16,'losp','tati18'),(17,'demonan','chany'),(18,'tati','1808ma');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-12-11 14:30:52
