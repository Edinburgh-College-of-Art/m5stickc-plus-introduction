##  Instructions for grabbing weather data from openMeteo.com

1. From GitHub, download OpenMeteo.ino
2. Read description: what does this sketch do?
3. Check out required actions and dependencies
4. Go to libraries and check if you have these installed // ArduinoHTTPClient (Arduino)
// ArduinoJSON (by Benoit Blanchon)
5. In OpenMeteo replace (NETWORK_NAME, NETWORK_PASSWORD) with your own details.
6. Set the coordinates of the place you want to get the weather forecast from as latitude and longitude values
// set coordinates, retrieve weather data
7. Connect your M5Stick and ensure your port and board are correct
8. Verify and upload your sketch
9. Read off the Location, Date, and weather information on your M5 Stick.
10. Try out some different locations by changing the latitude and longitude coordinates.
11. If you unplug M5, switch if off then switch on again tomorrow (assuming the same wifi network is accessible), you will get the updated forecast for the latest location you chose.
