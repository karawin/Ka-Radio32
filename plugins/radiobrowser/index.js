kaPlugin('radiobrowser', `<form name="radioBrowser">
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
	</div>
`, 1);