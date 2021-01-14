<?php 
/*header("Refresh: 60");*/

if (isset($_GET["Led1on"])) {
	echo "\n Reply From Server :".sendCMD("Bed led1 on");
}

if (isset($_GET["Led1off"])) {
	echo "\n Reply From Server :".sendCMD("Bed led1 off");
}

if (isset($_GET["checkled1"])) {

	$message = "Bed led1 on";
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

/*
//Hieronder de refreshes

//Bed
$bed_led1 = sendCMD("Bed check led1");
$bed_pushbutton1 = sendCMD("Bed check pushbutton1");
$bed_force = sendCMD("Bed check force");

//Chair
$chair_led1 = sendCMD("Chair check led1");
$chair_motor = sendCMD("Chair check motor");
$chair_pushbutton1 = sendCMD("Chair check pushbutton1");
$chair_force = sendCMD("Chair check force");

//Column
$column_led1 = sendCMD("Column check led1");
$column_pushbutton1 = sendCMD("Column check pushbutton1");
$column_co2 = sendCMD("Column check co2");

//Door
$door_door = sendCMD("Door check door");
$door_led1 = sendCMD("Door check led1");
$door_led2 = sendCMD("Door check led2");
$door_pushbutton1 = sendCMD("Door check pushbutton1");
$door_pushbutton2 = sendCMD("Door check pushbutton2");

//Fridge
$fridge_door = sendCMD("Fridge check fridgedoor")
$fridge_temp1 = sendCMD("Fridge check temp1")
$fridge_temp2 = sendCMD("Fridge check temp2")

//Tablelamp
$tablelamp_led1 = sendCMD("Tablelamp check led1");
$tablelamp_sensor = sendCMD("Tablelamp check sensor");

//Wall
$wall_ldr = sendCMD("Wall check ldr");
$wall_led1 = sendCMD("Wall check led1");
$wall_potentiometer = sendCMD("Wall check potmeter");

*/

?>

<?php
function sendCMD($message){
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
	// Close socket
	socket_close($socket);
	return $result;
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
        integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
    <title>Hier moet je zijn</title>
</head>

<body>
    <div class="container" style="margin-bottom: 5em;">
        <div class="row">
            <div class="col-md-12">
                <h1>Hallo Peter</h1>
            </div>

            <div id="bed" class="col-lg-6">
                <section>
                    <h2>Bed</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

            <div id="chair" class="col-lg-6">
                <section>
                    <h2>Chair</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Motor:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Motor aan</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

            <div id="column" class="col-lg-6">
                <section>
                    <h2>Column</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

            <div id="door" class="col-lg-6 flex-nowrap">
                <section>
                    <h2>Door</h2>
                    <table>
                        <tr>
                            <td><p>Led 1:</p></td>
                            <td><p><?php echo $bed_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="Led1on" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Led 2:</p></td>
                            <td><p><?php echo $bed_pushbutton1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="Led1off" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Deur:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="checkled1" class="btn-block btn-sm btn-info">Deur open</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

	        <div id="fridge" class="col-lg-6">
                <section>
                    <h2>Fridge</h2>
                    <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut
                        labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco
                        laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in
                        voluptate velit esse cillum dolore eu fugiat nulla pariatur.</p>
                </section>
            </div> 
            
            <div id="tablelamp" class="col-lg-6">
                <section>
                    <h2>Lamp</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>
            
            <div id="wall" class="col-lg-6">
                <section>
                    <h2>Wall</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Led aan</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Verduistervenster:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">Venster open</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>RGB:</p></td>
                            <td><p>?</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="" class="btn-block btn-sm btn-info">RGB aan</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

        </div>
    </div>

    <script>
        function greeting() {
            var today = new Date();
            var hourNow = today.getHours();
            var greeting;
            switch(hourNow) {
                case (hourNow > 18): greeting = 'Goedeavond Peter'; break;
                case (hourNow > 12): greeting = 'Goedemiddag Peter'; break;
                case (hourNow > 10): greeting = 'Goedemorgen Peter'; break;
                default: 'Hallo Peter';
            }
            var h = document.createElement("H1");
            h.appendChild(greeting);
            document.body.appendChild(h);
            // document.write('<h1>' + greeting + '</h1>');
        }
    </script>

</body>

</html>
