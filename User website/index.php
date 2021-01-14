<?php 
/*header("Refresh: 60");*/

if (isset($_GET["bed_led1_on"])) { echo "\n Reply From Server :".sendCMD("Bed led1 on"); }
if (isset($_GET["bed_led1_on"])) { echo "\n Reply From Server :".sendCMD("Bed led1 off"); }

if (isset($_GET["chair_led1_on"])) { echo "\n Reply From Server :".sendCMD("Chair led1 on"); }
if (isset($_GET["chair_led1_off"])) { echo "\n Reply From Server :".sendCMD("Chair led1 off"); }
if (isset($_GET["chair_motor_on"])) { echo "\n Reply From Server :".sendCMD("Chair motor on"); }
if (isset($_GET["chair_motor_off"])) { echo "\n Reply From Server :".sendCMD("Chair motor off"); }

if (isset($_GET["column_led1_on"])) { echo "\n Reply From Server :".sendCMD("Column led1 on"); }
if (isset($_GET["column_led1_off"])) { echo "\n Reply From Server :".sendCMD("Column led1 off"); }

if (isset($_GET["door_led1_on"])) { echo "\n Reply From Server :".sendCMD("Door led1 on"); }
if (isset($_GET["door_led1_off"])) { echo "\n Reply From Server :".sendCMD("Door led1 off"); }
if (isset($_GET["door_led2_on"])) { echo "\n Reply From Server :".sendCMD("Door led2 on"); }
if (isset($_GET["door_led2_off"])) { echo "\n Reply From Server :".sendCMD("Door led2 off"); }
if (isset($_GET["door_door_open"])) { echo "\n Reply From Server :".sendCMD("Door door open"); }
if (isset($_GET["door_door_close"])) { echo "\n Reply From Server :".sendCMD("Door door close"); }

if (isset($_GET["tablelamp_led1_on"])) { echo "\n Reply From Server :".sendCMD("Tablelamp led1 on"); }
if (isset($_GET["tablelamp_led1_off"])) { echo "\n Reply From Server :".sendCMD("Tablelamp led1 off"); }

if (isset($_GET["wall_led1_on"])) { echo "\n Reply From Server :".sendCMD("Wall led1 on"); }
if (isset($_GET["wall_led1_off"])) { echo "\n Reply From Server :".sendCMD("Wall led1 off"); }
if (isset($_GET["wall_lcd_on"])) { echo "\n Reply From Server :".sendCMD("Wall lcd on"); }
if (isset($_GET["wall_lcd_off"])) { echo "\n Reply From Server :".sendCMD("Wall lcd off"); }


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
$wall_lcd = sendCMD("Wall check lcd");
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
                <h1>Hello Peter</h1>
            </div>

            <div id="bed" class="col-lg-6">
                <section>
                    <h2>Bed</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td><p><?php echo $bed_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="bed_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="bed_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Force:</p></td>
                            <td><p><?php echo $bed_force; ?></p></td>
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
                            <td><p><?php echo $chair_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="chair_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="chair_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Motor:</p></td>
                            <td><p><?php echo $chair_motor; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="chair_motor_on" class="btn-block btn-sm btn-info">Turn motor on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="chair_motor_off" class="btn-block btn-sm btn-info">Turn motor off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Force:</p></td>
                            <td><p><?php echo $chair_force; ?></p></td>
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
                            <td><p><?php echo $column_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Buzzer:</p></td>
                            <td><p></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_pushbutton1_on" class="btn-block btn-sm btn-info">Turn buzzer on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_pushbutton1_off" class="btn-block btn-sm btn-info">Turn buzzer off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>CO2:</p></td>
                            <td><p><?php echo $column_co2; ?></p></td>
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
                            <td><p><?php echo $door_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Led 2:</p></td>
                            <td><p><?php echo $door_led2; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_led2_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_led2_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Door:</p></td>
                            <td><p><?php echo $door_door; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_door_open" class="btn-block btn-sm btn-info">Open door</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="door_door_close" class="btn-block btn-sm btn-info">Close door</button>
                                </form>
                            </td>
                        </tr>
                    </table>
                </section>
            </div>

	        <div id="fridge" class="col-lg-6">
                <section>
                    <h2>Fridge</h2>
                    <table>
                        <tr>
                            <td><p>Fridge door:</p></td>
                            <td><p><?php echo $fridge_door; ?></p></td>
                        </tr>
                        <tr>
                            <td><p>Temperature 1:</p></td>
                            <td><p><?php echo $fridge_temp1; ?></p></td>
                        </tr>
                        <tr>
                            <td><p>Temperature 2:</p></td>
                            <td><p><?php echo $fridge_temp2; ?></p></td>
                        </tr>
                    </table>
                </section>
            </div> 
            
            <div id="tablelamp" class="col-lg-6">
                <section>
                    <h2>Lamp</h2>
                    <table>
                        <tr>
                            <td><p>Led :</p></td>
                            <td><p><?php echo $tablelamp_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="tablelamp_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="tablelamp_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>Sensor:</p></td>
                            <td><p><?php echo $tablelamp_sensor; ?></p></td>
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
                            <td><p><?php echo $wall_led1; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_led1_on" class="btn-block btn-sm btn-info">Turn led on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_led1_off" class="btn-block btn-sm btn-info">Turn led off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>LCD:</p></td>
                            <td><p><?php echo $wall_lcd; ?></p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_lcd_on" class="btn-block btn-sm btn-info">Turn LCD on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_lcd_off" class="btn-block btn-sm btn-info">Turn LCD off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>LDR:</p></td>
                            <td><p><?php echo $wall_ldr; ?></p></td>
                        </tr>
                        <tr>
                            <td><p>Potentiometer:</p></td>
                            <td><p><?php echo $wall_potentiometer; ?></p></td>
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
                case (hourNow > 18): greeting = 'Good evening Peter'; break;
                case (hourNow > 12): greeting = 'Good afternoon Peter'; break;
                case (hourNow > 10): greeting = 'Good morning Peter'; break;
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
