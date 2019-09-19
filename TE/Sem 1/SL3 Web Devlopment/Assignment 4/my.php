<html>

<head>
  <title>
    PHP Trial
  </title>
  <script>
  </script>
</head>

<body>

  <?php

  // DECLARING VAR
  $flag = TRUE;
  $email = $website = $url = $name = $pw = $pw2 = "";

  // TAKING INPUT IN GLOBAL VAR
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["email"];
    $name = $_POST["name"];
    $pw = $_POST["password"];
    $pw2 = $_POST["password2"];
    $website = $_POST["website"];
  }
  ?>

  <form method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" role="form" id="myform"><br>
    <input name="name" placeholder="Name"><br>
    <input name="email" placeholder="Email"><br>
    <input name="website" placeholder="website"><br>
    <input name="password" type="password" placeholder="Password"><br>
    <input name="password2" type="password" placeholder="Reenter Password"><br>
    <input type="submit" value="Submit"><br>
    <hr>
  </form>
  <?php

  if (empty($email)) {
    echo "<br>*Please Enter The Email";
    $flag = FALSE;
  } else {
    if (!preg_match("/^([a-z0-9\+_\-]+)(\.[a-z0-9\+_\-]+)*@([a-z0-9\-]+\.)+[a-z]{2,6}$/ix", $email)) {
      echo "<br>Invalid Email Entered !!";
      $flag = FALSE;
    }
  }

  if (empty($name)) {
    echo "<br>*Please Enter The name";
    $flag = FALSE;
  }

  if (empty($pw) || empty($pw2)) {
    echo "<br>*Please Enter The Password";
    $flag = FALSE;
  } else {
    if ($pw != $pw2) {
      echo "<br>*Password Did not Matched !";
      $flag = FALSE;
    }
  }
  if (empty($website)) {
    echo "*<br>* ENTER URL";
    $flag = FALSE;
  } else {
    if (!preg_match("/^(http:\/\/www\.|https:\/\/www\.|http:\/\/|https:\/\/)?[a-z0-9]+([\-\.]{1}[a-z0-9]+)*\.[a-z]{2,5}(:[0-9]{1,5})?(\/.*)?$/ix", $website)) {
      echo "<br>* Invalid URL";
      $flag = FALSE;
    }
  }

  if($flag)
  {
    header("Location: form.html");
    exit;
  }
  ?>


</body>

</html>
