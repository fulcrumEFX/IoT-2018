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
if($conn == false){
die("ERROR Could not connect to SQL.".mysqli_connect_error());
}
 
$sql2= "SELECT * FROM Tabelle01";
$result_1 = mysql_query($conn, $sqL2);
 
//IN TABELLE ANZEIGEN
if ($result_1->num_rows >0){
    echo "<b> Status of Sensor 1: </b>";
    echo "<table border=1><tr><th>X1</th><th>X2</th><th>Message</th></tr>";
    //jede Reihe daten ausgeben
    while($row= $result_1->fetch_assoc()){
        echo "<tr><td>".$row["X1"]."</td><td>".$row["X2"]."</td><td>".$row["msg"]."</td></tr>";
    }
    echo "</table>";
} else{
        echo "0 Results";
}
 
?>
</body>
</html>
