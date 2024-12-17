<?php
// Database configuration
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "motion_detection";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get data from the request
$motion_status = isset($_POST['motion_status']) ? $_POST['motion_status'] : null;

if ($motion_status) {
    // Insert data into the database
    $sql = "INSERT INTO motion_data (motion_status, timestamp) VALUES ('$motion_status', NOW())";

    if ($conn->query($sql) === TRUE) {
        echo "Motion data saved successfully.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "No motion data provided.";
}

// Close connection
$conn->close();
?>
