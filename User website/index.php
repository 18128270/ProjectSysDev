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
	<h1 id="welcome"></h1>
        <div class="col-md-12"></div>
            <div class="row">
            <div class="col-lg-6">
                <section>
                    <h2>Go to Peter's Page</h2>
                    <table>
                        <form action="/OwnersPage.php">
                            <button type="submit" class="btn-block btn-sm btn-info">Go to Peter's Page</button>
                        </form>
                    </table>
                </section>
            </div>

            <div class="col-lg-6">
                <section>
                    <h2>Go to Control Page</h2>
                    <table>
                        <form action="/ControlPage.php">
                            <button type="submit" class="btn-block btn-sm btn-info">Go to Control Page</button>
                        </form>
                    </table>
                </section>
            </div>

	        <div class="col-lg-6">
                <section>
                    <h2>Go to the Test Page</h2>
                    <table>
                        <form action="/TestPage.php">
                            <button type="submit" class="btn-block btn-sm btn-info">Go to Test Page</button>
                        </form>
                    </table>
                </section>
            </div>
	    
	        <div class="container" style="margin-bottom: 5em;">
                <h1>About us: </h>
                <section>
		            <img src="Peter_is_Here.jpg" alt="Italian Trulli">
                </section>
            </div>
        </div>
    </div>
</body>

<script>
var today = new Date();
var hourNow = today.getHours();
var greeting;
if(hourNow > 8){
	greeting = "Good morning";
}
if(hourNow>12){
	greeting = "Good afternoon";
}
if(hourNow>18){
	greeting = "Good evening";
}
if(hourNow<8){
	greeting = "Good night";
}

document.getElementById("welcome").innerHTML = greeting;
</script>

</html>

