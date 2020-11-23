<?php 

require_once 'C:\xampp\htdocs\wappbot\webhoohphp.php';  
 
use IFTTT\Http\Request;
use Twilio\Rest\Client; 

if(isset($_GET[ACfbfad2ee8918acf077bab27a36ac3ac8]) && isset($_GET[6d76c2a4f9ac79c370162a136730dae9]) && isset($_GET["body"]) && isset($_GET[12019756599]) && isset($_GET[919381374776])){
	$sid    = $_GET[ACfbfad2ee8918acf077bab27a36ac3ac8]; 
    $token  = $_GET[6d76c2a4f9ac79c370162a136730dae9];  
    $twilio = new Client($sid, $token);
	 $response = $client->request('GET', "https://maker.ifttt.com/trigger/whatsapp_bot/with/key/1Gqafn9c40o6PDLoDbfNr");
	$response = json_decode($response->getBody())
	if($response->getStatusCode() == 200) {
                $message = "*temp: *$Response->temp\n";
                $message = "*humidity:* $Response->humidity\n";
               }
	$to = $_GET['to'];
	$from = $_GET['from'];
	$body = $_GET['body'];
	
	$message = $twilio->messages 
                  ->create(919381374776.$to, 
                           array( 
                               "from" => 12019756599.$from,       
                               "body" => $body
                           ) 
                  );
    echo 'Message Send...';				  
	
}

else{
	echo "There is no request yet! Copy this link(webhook) and make an HTTP Get Request from your device.";
}

?>
