# Welcome to the IoTea Project!

## What?

Take a camera. Add an object recognition algorithm. Hide the whole thing in a teabox (optional). Send the data to the cloud. Access it anywhere. Monitor traffic at an intersection, or in your business. Spy on your airbnb guests. Who needs privacy, when you can have smart cities? This is IoTea.

## Why?

This project was the work of four GreenFox Academy students, created during a 24-hour hackaton. Fun fact: none of us are web development students. Yet look at this site! Look at the magic of cloud-logging! Unbelievable.

## How?

A Raspberry Pi 4 is hidden inside a tea box. It is running a C++ application using OpenCV and YOLO as its object recognition brain. Every minute, it logs the collected and formatted data to a remote hosted database. MySQL, Python, and cron are working hand-in-hand to accomplish this task.

