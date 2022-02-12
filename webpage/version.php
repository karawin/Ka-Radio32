<?php header('Access-Control-Allow-Origin: *'); ?>
<!-- saved from url=(0037)http://karadio.karawin.fr/version.php -->
<!DOCTYPE html>
<html>
<body>

    <p><span class="label label-success">Release <span id="firmware_last">2.1 Rev 1 </span> - Built on 2021/03/12
	</span>
	</p>
	
    New:
	<ul id="ordered">
		<li> 2.1 R1: 
		<ul id="ordered">
		<li> Some mistakes on the wifi init for AP1 and AP2</li>
		</ul></li>
		<li> 2.1 R0: 
		<ul id="ordered">
		<li>Security: the ssid passwords are no longer sent on each "Setting" display, but only when changed.</li>
		<li>Bug fixed: in parse playlist. Possible memory leak. Thanks to HmarikBel</li>
		<li>Bug fixed: Special char in station name was incorrectly sent.</li>
		<li>Some minors improvements.</li>
		</ul></li>				<li> 2.0 R0: 
		<ul id="ordered">
		<li> Better handling of the large "header moved"</li> 
		<li> Better monitoring</li> 
		<li> timezone suggestion on the setting page</li>
		</ul></li>	
    </ul>

    <div class="alert alert-danger">
        <h4 class="trn">Warning!</h4>
        <p class="trn">If you experiment some strange problems with karadio, please check if the adc (A0) pin is wired to Ground if you don't have a control panel.</p>
    </div>
	</p>
</body>
</html>