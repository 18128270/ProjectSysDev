<?php 
header("Refresh: 60");

if (isset($_GET["bed_led1_on"])) { echo "\n Reply From Server :".sendCMD("Bed led1 on"); }
if (isset($_GET["bed_led1_off"])) { echo "\n Reply From Server :".sendCMD("Bed led1 off"); }

if (isset($_GET["chair_led1_on"])) { echo "\n Reply From Server :".sendCMD("Chair led1 on"); }
if (isset($_GET["chair_led1_off"])) { echo "\n Reply From Server :".sendCMD("Chair led1 off"); }
if (isset($_GET["chair_motor_on"])) { echo "\n Reply From Server :".sendCMD("Chair motor on"); }
if (isset($_GET["chair_motor_off"])) { echo "\n Reply From Server :".sendCMD("Chair motor off"); }

if (isset($_GET["column_led1_on"])) { echo "\n Reply From Server :".sendCMD("Column led1 on"); }
if (isset($_GET["column_led1_off"])) { echo "\n Reply From Server :".sendCMD("Column led1 off"); }
if (isset($_GET["column_buzzer_on"])) { $column_buzzer = 1; echo "\n Reply From Server :".sendCMD("Column buzzer on");  }
if (isset($_GET["column_buzzer_off"])) { $column_buzzer = 0; echo "\n Reply From Server :".sendCMD("Chair buzzer off");  }

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

//Hieronder de refreshes

function RefreshBed(){
    $bed_led1 = sendCMD("Bed check led1");
    $bed_force = sendCMD("Bed check force"); 
}

function RefreshChair(){
    $chair_led1 = sendCMD("Chair check led1");
    $chair_motor = sendCMD("Chair check motor");
    $chair_force = sendCMD("Chair check force");

}

function RefreshColumn(){
    $column_led1 = sendCMD("Column check led1");
    $column_co2 = sendCMD("Column check co2");
}

function RefreshDoor(){
    $door_door = sendCMD("Door check door");
    $door_led1 = sendCMD("Door check led1");
    $door_led2 = sendCMD("Door check led2");
}
function RefreshFridge(){
    $fridge_temp1 = sendCMD("Fridge check temp1");
    $fridge_temp2 = sendCMD("Fridge check temp2");
}

function RefreshTablelamp(){
    $tablelamp_led1 = sendCMD("Tablelamp check led1");
    $tablelamp_sensor = sendCMD("Tablelamp check sensor");
}

function RefreshWall(){
    $wall_lcd = sendCMD("Wall check lcd");
    $wall_ldr = sendCMD("Wall check ldr");
    $wall_led1 = sendCMD("Wall check led1");
}

/*
RefreshBed();
RefreshChair();
RefreshColumn();
RefreshDoor();
RefreshFridge();
RefreshTablelamp();
RefreshWall();
*/


?>

<?php
function sendCMD($message){
	$host = "192.168.4.1";
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
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.2/css/all.min.css">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
        integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
        	<!-- ****** favicons ****** -->
	<link rel="shortcut icon" href="/VicBigDick.ico">
	<link rel="icon" sizes="16x16 32x32 64x64" href="/VicBigDick.ico">
	<link rel="icon" type="image/png" sizes="196x196" href="/VicBigDick-192.png">
	<link rel="icon" type="image/png" sizes="160x160" href="/VicBigDick-160.png">
	<link rel="icon" type="image/png" sizes="96x96" href="/VicBigDick-96.png">
	<link rel="icon" type="image/png" sizes="64x64" href="/VicBigDick-64.png">
	<link rel="icon" type="image/png" sizes="32x32" href="/VicBigDick-32.png">
	<link rel="icon" type="image/png" sizes="16x16" href="/VicBigDick-16.png">
	<link rel="apple-touch-icon" href="/VicBigDick-57.png">
	<link rel="apple-touch-icon" sizes="114x114" href="/VicBigDick-114.png">
	<link rel="apple-touch-icon" sizes="72x72" href="/VicBigDick-72.png">
	<link rel="apple-touch-icon" sizes="144x144" href="/VicBigDick-144.png">
	<link rel="apple-touch-icon" sizes="60x60" href="/VicBigDick-60.png">
	<link rel="apple-touch-icon" sizes="120x120" href="/VicBigDick-120.png">
	<link rel="apple-touch-icon" sizes="76x76" href="/VicBigDick-76.png">
	<link rel="apple-touch-icon" sizes="152x152" href="/VicBigDick-152.png">
	<link rel="apple-touch-icon" sizes="180x180" href="/VicBigDick-180.png">
	<meta name="msapplication-TileColor" content="#FFFFFF">
	<meta name="msapplication-TileImage" content="/VicBigDick-144.png">
	<meta name="msapplication-config" content="/browserconfig.xml">
	<!-- ****** favicons ****** -->
    <title>PSDV GP11</title>
    
</head>

<body>
    <div class="container" style="margin-bottom: 5em;">
	<h1 id="welcome">PETER</h1>
        <div class="col-md-12"></div>
            <div class="row">
            <div id="bed" class="col-lg-6">
                <section>
                    <h2>Bed</h2>
                    <table>
                        <tr>
                            <td><p>Led:</p></td>
                            <td> <i id="Bedled1" class="fas fa-lightbulb" style="color:gray"></i> </td>
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
			                <td> <i id="BedForce" class="fas fa-bed" style="color:gray"></i> </td>
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
                            <td><p> <i id="Chairled1" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="ChairMotor" class="fas fa-power-off" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="ChairForce" class="fas fa-chair" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Columnled1" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Columnbuzzer" class="fas fa-volume-up"</p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_buzzer_on" class="btn-block btn-sm btn-info">Turn buzzer on</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="column_buzzer_off" class="btn-block btn-sm btn-info">Turn buzzer off</button>
                                </form>
                            </td>
                        </tr>
                        <tr>
                            <td><p>CO2:</p></td>
			                <td><p> <i id="Columnco2" class="fas fa-exclamation-triangle" ></i> </p></td>
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
                            <td><p> <i id="Doorled1" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Doorled2" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Doordoor" class="fas fa-door-open" style="color:gray"></i> </p></td>
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
			                <td><p> <i id="Fridgedoor" class="fas fa-door-open" style="color:gray"></i> </p></td>
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
                            <td><p>Led:</p></td>
                            <td><p> <i id="Lampled1" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Lampsensor" class="fas fa-exclamation-circle" style="color:gray"></i> </p></td>
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
                            <td><p> <i id="Wallled1" class="fas fa-lightbulb" style="color:gray"></i> </p></td>
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
                            <td><p>Blinds:</p></td>
                            <td><p> <i id="Walllcd" class="fas fa-person-booth" style="color:gray"></i> </p></td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_lcd_on" class="btn-block btn-sm btn-info">Close blinds</button>
                                </form>
                            </td>
                            <td>
                                <form action="" method="get">
                                <button type="submit" name="wall_lcd_off" class="btn-block btn-sm btn-info">Open blinds</button>
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

</body>

<?php
// Icon color change based on state
if($bed_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Bedled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Bedled1").style.color="Tomato";';
    echo '</script>';	
}

if($bed_force == 1){
    echo '<script>';
    echo 'document.getElementById("BedForce").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("BedForce").style.color="Tomato";';
    echo '</script>';	
}

if($chair_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Chairled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Chairled1").style.color="Tomato";';
    echo '</script>';	
}

if($chair_motor == 1){
    echo '<script>';
    echo 'document.getElementById("ChairMotor").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("ChairMotor").style.color="Tomato";';
    echo '</script>';	
}

if($chair_force == 1){
    echo '<script>';
    echo 'document.getElementById("ChairForce").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("ChairForce").style.color="Tomato";';
    echo '</script>';	
}

if($column_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Columnled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Columnled1").style.color="Tomato";';
    echo '</script>';
}

if($column_buzzer == 1){
    echo '<script>';
    echo 'document.getElementById("Columnbuzzer").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Columnbuzzer").style.color="Tomato";';
    echo '</script>';
}

if($column_co2 == 1){
    echo '<script>';
    echo 'document.getElementById("Columnco2").style.color="Lime";';
    echo 'alert("shits on fire yo")';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Columnco2").style.color="Tomato";';
    echo '</script>';
}

if($door_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Doorled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Doorled1").style.color="Tomato";';
    echo '</script>';
}

if($door_led2 == 1){
    echo '<script>';
    echo 'document.getElementById("Doorled2").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Doorled2").style.color="Tomato";';
    echo '</script>';
}

if($door_door == 1){
    echo '<script>';
    echo 'document.getElementById("Doordoor").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Doordoor").style.color="Tomato";';
    echo '</script>';
}

if($fridge_door == 2){
    echo '<script>';
    echo 'document.getElementById("Fridgedoor").style.color="Lime";';
    echo 'alert("Your fridge door is open too damn long")';
    echo '</script>';
}

if($fridge_door == 1){
    echo '<script>';
    echo 'document.getElementById("Fridgedoor").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Fridgedoor").style.color="Tomato";';
    echo '</script>';
}

if($tablelamp_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Lampled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Lampled1").style.color="Tomato";';
    echo '</script>';
}

if($tablelamp_sensor == 1){
    echo '<script>';
    echo 'document.getElementById("Lampsensor").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Lampsensor").style.color="Tomato";';
    echo '</script>';
}

if($wall_led1 == 1){
    echo '<script>';
    echo 'document.getElementById("Wallled1").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Wallled1").style.color="Tomato";';
    echo '</script>';
}

if($wall_lcd == 1){
    echo '<script>';
    echo 'document.getElementById("Walllcd").style.color="Lime";';
    echo '</script>';
    } else {
    echo '<script>';
    echo 'document.getElementById("Walllcd").style.color="Tomato";';
    echo '</script>';
}

?>

<script>
    var today = new Date();
    var hourNow = today.getHours();
    var greeting;
    if(hourNow > 8){
	    greeting = "Good morning hackerboy";
    }
    if(hourNow>12){
	    greeting = "Good afternoon hackerboy";
    }
    if(hourNow>18){
	    greeting = "Good evening hackerboy";
    }
    if(hourNow<8){
	    greeting = "Good night hackerboy";
    }

    document.getElementById("welcome").innerHTML = greeting;

</script>

</html>

