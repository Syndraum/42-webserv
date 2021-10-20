<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<link rel="icon" type="image/png" sizes="32x32" href="/assets/favicon-32x32.png">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Form GET</title>

    <!-- CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    <link href="/assets/style.css" rel="stylesheet">
  </head>

  <body>
	<div class="container-fluid">
		<div class="row justify-content-center">
			<div class="col-11 col-lg-9">
				<div class="row mt-5">
					<div class="col-12">
						<a href="/"><h1 class="fs-1 fw-bold">Webserviette</h1></a>
					</div>
				</div>
				<div class="row mt-3">
					<div class="col-12 col-md-9 col-xl-7 mb-5">
						<h3>GET Form : result</h3>
						<p>
							Les données du formulaire s'affichent ci-dessous. <br>Observez bien l'url. Il se compose de la ressource <span class="code-text">form_get.php</span>, d'un séparateur <span class="code-text">?</span>, et d'argument au format <span class="code-text">nom=valeur</span><br>
							Essayez de changer ses valeurs à la main et relancez la requête.
						</p>
						<div class="code">
							Email : <span class="fw-light"><?php echo $_GET['email'] ?></span>
							<br>
							Login : <span class="fw-light"><?php echo $_GET['login'] ?></span>
						</div>
						<a class="link d-inline-flex flex-row align-items-center mt-5" href="/form.html">
							<span class="link-text me-5 fs-5">Retour au formulaire</span>
							<svg class="link-arrow" xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="#0437ce" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
								<line x1="4" y1="12" x2="20" y2="12"/>
								<polyline points="14 6 20 12 14 18"/>
							</svg>
						</a>
					</div>
				</div>
			</div>
		</div>
	</div>
</body>
</html>