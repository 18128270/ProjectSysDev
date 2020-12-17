<?php 

if (isset($_GET["submit"])) {

	$message = $_GET["query"];
	$host = "192.168.178.57";
	$port = 8080;
	error_reporting(E_ALL);

	// create socket
	$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

	// connect to server
	$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");

	// Send string to server
	socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");

	// Get server response
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
        Query: <input type="text" name="query">
        <button type="submit" name="submit">Submit!</button>
    </form>
</body>
</html>

