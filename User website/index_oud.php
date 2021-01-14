<?php 

if (isset($_GET["Led1on"])) {

	$message = "bed on";
	$host = "192.168.178.21";
	$port = 8080;
	error_reporting(E_ALL);

	// create socket
	$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

	// connect to server
	$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");

	// Send Destination to server
	socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
	$result = socket_read ($socket, 1024) or die("Could not read server response\n");
	echo "\nReply From Server :".$result;

	// Close socket
	socket_close($socket);
}

if (isset($_GET["Led1off"])) {

	$message = "bed off";
	$host = "192.168.178.21";
	$port = 8080;
	error_reporting(E_ALL);

	// create socket
	$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

	// connect to server
	$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");
	
	// Send Destination to server
	socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
	$result = socket_read ($socket, 1024) or die("Could not read server response\n");
	echo "\nReply From Server :".$result;

	// Close socket
	socket_close($socket);
}

if (isset($_GET["submit"])) {

	$message = "Bed";
	$host = "192.168.178.21";
	$port = 8080;
	error_reporting(E_ALL);

	// create socket
	$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

	// connect to server
	$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");
	
	// Send msg
	socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
	$result = socket_read ($socket, 1024) or die("Could not read server response\n");
	echo "Reply From Server :".$result;

	// Close socket
	socket_close($socket);
}

?>


<html>
<head>
</head>
<body>
    <form action="index.php" method="get">
        <button type="submit" name="Led1on">Led 1 aan</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="Led1off">Led 1 uit</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>
	<form action="index.php" method="get">
        <button type="submit" name="submit">Submit!</button>
    </form>

</body>
</html>

