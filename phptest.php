<html> <head>
<title>PHP Beispiel</title>
 
<script>
 
</script>
 
<meta http-quiv="refresh" content=1>
</head>
 
<style>
 table{
border-collapse: collapse;
}
</style>
 
<body>
 
<?php
 
echo "<br>";
 
//SQL server cfg
$servername = "localhost";
$username = "root";
$password = "iot2018";
$dbname = "EddyDB";
 
$conn=mysqli_connect($servername, $username, $password, $dbname);
if($conn === false){
	die("ERROR Could not connect to SQL.".mysqli_connect_error());
}
 
$sql2= "SELECT * FROM gpio_status";
$result_1 = mysqli_query($conn, $sql2);
 
//IN TABELLE ANZEIGEN
if ($result_1->num_rows >0){
    echo "<b> Status of Sensor 1: </b>";
    echo "<table border=1><tr><th>ID</th><th>Broker</th><th>Topic</th><th>Message</th><th>QOS</th><th>retain</th><th>Time_received</th></tr>";
    //jede Reihe daten ausgeben
    while($row= $result_1->fetch_assoc()){
        echo "<tr><td>".$row["ID"]."</td><td>".$row["Broker"]."</td><td>".$row["Topic"]."</td><td>".$row["Message"]."</td><td>".$row["QOS"]."</td><td>".$row["retain"]."</td><td>".$row["Time_received"]."</td></tr>";
    }
    echo "</table>";
} else{
        echo "0 Results";
}
 
?>
</body>
</html>
