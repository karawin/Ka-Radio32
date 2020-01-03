<?php

const HOSTNAME = 'https://de1.api.radio-browser.info';
const TITLE = 'Radio Browser';
const ID = 'radiobrowser';

function innerHTML() {
?>
<form name="radioBrowser">
	<div class="text">
		<label for="name">Name</label>
		<input type="text" id="name" name="name" value="" />
	</div>
	<div>
		<label for="country">Country</label>
		<select id="country" name="country">
			<option value="">---</option>
		</select>
	</div>
	<div>
		<label for="state">State</label>
		<select id="state" name="state">
			<option value="">---</option>
		</select>
	</div>
	<div>
		<label for="language">Language</label>
		<select id="language" name="language">
			<option value="">---</option>
		</select>
	</div>
	<div class="text">
		<label for="tag">Tag</label>
		<input type="text" id="tag" name="tag" value="" />
	</div>
	<div>
		<input name="submit" type="submit" />
	</div>
</form>
<div id="rb-stations">
	<table>
		<thead></thead>
		<tbody></tbody>
	</table>
</div>
<?php
}

function getContainerName() {
	$t = dirname($_SERVER['SCRIPT_NAME']);
	return substr($t, strrpos($t, '/') + 1);
}

function make_body($callback=false) {
	if(is_string($callback)) {
		echo "$callback('" . getContainerName() . "', `";
	}

	innerHTML();

	if(is_string($callback)) {
?>
	</div>
<?php
		$script = (file_exists(__DIR__ . '/script.js')) ? ', 1' : '';
		echo "`$script);";
	}
}

if(!empty($_SERVER)) {
	if(filter_has_var(INPUT_GET, 'innerHTML')) {
		$innerHTML = filter_input(INPUT_GET, 'innerHTML', FILTER_SANITIZE_STRING);
		header('Content-Type: application/javascript; charset=utf-8');
		make_body($innerHTML);
		exit;
	}

?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<title>Calm Radio</title>
	<link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body id="<?= ID ?>">
<?php make_body(); ?>
<?php
	if(empty($callback) and file_exists(__DIR__ . '/script.js')) {
?>
	<script type="text/javascript" src="script.js"></script>
<?php
	}
?>
</body></html>
<?php
	exit;
}

?>
