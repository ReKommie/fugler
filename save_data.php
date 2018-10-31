ok	- save file
<?php
// Decodes received JSON and dumps selected fields to datalog.txt
	$headers = getallheaders();
	if ($headers["Authorization"] == "elsys") {
		$json_str = file_get_contents('php://input');
		$json_obj = json_decode($json_str, true);
		// load selected data fields into PHP array
		// look at the JSON file from the previous example to know decide fields to access
		$mydata = array(
			'led' => $json_obj['payload_fields']['led'],
			'time' => $json_obj['metadata']['time'],
			'gateways' => $json_obj['metadata']['gateways']
		);
		// write the data fields to a log file (in text format)
		// in principle, anything you want can be done with the data, 
		// e.g. saving it in a database
		$file = fopen("datalog.txt","a"); // NB! "a" appends to the file, "w" overwrites the file
		fwrite($file, $json_str);
		foreach ($mydata['gateways'] as $gateway) { //loop through each gateway 
			fwrite($file, $gateway['gtw_id'].' ');
		}
		fwrite($file, PHP_EOL); // end of line
		fclose($file);
	}
?>