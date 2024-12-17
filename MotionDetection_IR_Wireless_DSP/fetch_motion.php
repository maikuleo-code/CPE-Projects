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

// Fetch the latest motion status
$sql = "SELECT motion_status FROM motion_data ORDER BY timestamp DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $status = $row['motion_status'];
} else {
    $status = "No Motion Detected"; // Default if no records are found
}

// Send JSON response
header('Content-Type: application/json');
echo json_encode(["motion_status" => $status]);

// Close connection
$conn->close();
?>
