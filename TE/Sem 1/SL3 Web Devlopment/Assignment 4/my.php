<html>

<head>
  <title>
    PHP Trial
  </title>
</head>

<body>
  <?php
  $email = $url = "";
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["name1"];
    $url = $_POST["name"];
  }
  ?>

  <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">

    <input  name="name1" placeholder="Email">

    <input name="name" placeholder="URL">

    <input type="submit" value="Submit">
  </form>
  <?php
  if (empty($email))
    echo "*Please Enter The Email";
  else {
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      echo "Invalid Email Entered !!";
    }
  }

  if (empty($url))
    echo "*Please Enter the URL";
  else{
    if (!filter_var($url, FILTER_VALIDATE_URL)) {
      echo "Invalid URL Entered !!";
    }
  }

  ?>


</body>

</html>
