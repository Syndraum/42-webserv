<!DOCTYPE html>
<html lang="en">
  <head>

    <!-- Declared Vars To Go Here -->

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Metadata -->
    <meta name="description" content="">
    <meta name="author" content="">

    <!-- Page Name and Site Name -->
    <title>Form</title>

    <!-- CSS -->
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
    <link href="mysource_files/style.css" rel="stylesheet">

  </head>

  <body>

    <div class="container">

		<h3>POST TEST</h3>
		<div>
			Email : <?php echo $_POST['email'] ?>
			<br>
			Login : <?php echo $_POST['login'] ?>
		</div>
    </div> <!-- /container -->

  </body>
</html>