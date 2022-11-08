<?php

$serverName = "119.82.141.196";
$uid= "huy";
$pwd= "Huyblackbox1@";
$databaseName = "testdb";

$CURRENT_TIMESTAMP = new Datetime();

/*
$la=41.40338;
$ln=2.1740;
$sp=3.7;
$X=4.5;
$Y=6.7;
$Z=7.8;
*/

if(isset($_GET['la'])) $la = $_GET['la'];
if(isset($_GET['ln'])) $ln = $_GET['ln'];
if(isset($_GET['sp'])) $sp = $_GET['sp'];
if(isset($_GET['X'])) $X = $_GET['X'];
if(isset($_GET['Y'])) $Y = $_GET['Y'];
if(isset($_GET['Z'])) $Z = $_GET['Z'];

echo "Finish setting";

$connectionInfo = array ( "UID"=>$uid, "PWD"=>$pwd, "Database"=>$databaseName);

$conn=sqlsrv_connect( $serverName, $connectionInfo);

if($conn)
{
        echo "Server is connected\n";
        $tsql = "INSERT INTO mydb1 (dateUploaded,lat,lng,speed,accX,accY,accZ) VALUES (?,?,?,?,?,?,?)";
        $var = array($CURRENT_TIMESTAMP,$la,$ln,$sp,$X,$Y,$Z);

        /* Execute the query */
        $stmt = sqlsrv_query($conn, $tsql, $var);
        if ($stmt)
        {
                echo "Statement executed. \n";
        }
        else
        {
                echo "Statement not executed. \n";
        }
}
else
{
        echo "Server is not connected\n";
}
?>
