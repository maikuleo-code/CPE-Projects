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

// Fetch the last 10 motion records (or more if needed)
$sql = "SELECT motion_status, timestamp FROM motion_data ORDER BY timestamp DESC LIMIT 10";
$result = $conn->query($sql);

$records = array();

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $records[] = $row;
    }
}

// Send JSON response
header('Content-Type: application/json');
echo json_encode($records);

// Close connection
$conn->close();
?>
