ok	- save file
<?php
// Dumps JSON to datalog.txt, one object per line
	$headers = getallheaders();
	if ($headers["Authorization"] == "elsys") {
		$json_str = file_get_contents('php://input');
		$file = fopen("datalog.txt","a"); // NB! "a" appends to the file, "w" overwrites the file
		fwrite($file, $json_str);
		fwrite($file, PHP_EOL); // end of line
		fclose($file);
	}
?>
