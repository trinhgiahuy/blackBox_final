<?php

$serverName = "119.82.141.196";
$server="(local)";
$uid= "huy";
$pwd= "Huyblackbox1@";
$databaseName = "testdb";

$connectionInfo = array ( "UID"=>$uid, "PWD"=>$pwd, "Database"=>$databaseName);

$conn=sqlsrv_connect( $serverName, $connectionInfo);

$sqlQuery = "select * from mydb where dateUploaded in (select max(dateUploaded) from mydb group by name)";

$query = sqlsrv_query($conn,$sqlQuery);
$res= [];

while ($row = sqlsrv_fetch_array($query, SQLSRV_FETCH_NUMERIC) ){
        $res[] = $row;
}

sqlsrv_free_stmt($query);
echo json_encode(['data' => $res]);
?>
