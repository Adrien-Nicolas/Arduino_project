# Arduino_project

Make with [![My Skills](https://skills.thijs.gg/icons?i=c,arduino)](https://skills.thijs.gg)

# Eq platform 

I bought a telescope to see stars, but I have encountered a problem : When I was observing the stars in my telescope, they were moving with the rotation of the earth. So I studied and modeled a project called 'Equatorial Platform'. This one, through its movement, and with the inclination equal to my latitude, allowed to follow the rotation of the earth.

![eqplatform](https://user-images.githubusercontent.com/73825898/171649408-0db79e62-6e50-4974-8f82-755c3d8e7a95.gif)
![Scheme jpg 454e704f426362fd6eff24decbf70fb9](https://user-images.githubusercontent.com/73825898/171650033-2c06a918-9030-4336-8ed8-06ef285b9087.jpg)

# Distance sensor

The distance sensor project came from a rather original idea: Can we warn motorists that a collision may happen and warn them just before it happens in order to be able to mitigate it?
To answer this question I wanted to do a little experiment. I therefore equipped myself with an ultrasonic sensor to calculate a distance from a surface, and I therefore calculated the speed of this surface approaching the sensor in order to be able to estimate the time remaining before the collision, and display a message alert.

# Demonstration

Let us imagine that in our case, the limit of safety distance not to exceed is 30 cm, the sensor (circled in red) will be laid out on the back bumper of the car, and will thus collect the front shock of the car preceding it. The yellow pocket on the following photo will thus represent the car which approaches. 

![experience1](https://user-images.githubusercontent.com/73825898/171686924-0244ff15-aea9-4cae-b2fd-98786e441aaf.png)

This one will be placed at a certain initial distance, the sensor will make a first measurement, the pocket getting closer, the sensor will take a new measurement of distance.

![experience2](https://user-images.githubusercontent.com/73825898/171686932-048191fd-bdb2-42e5-91f4-22b0b8c25d2c.png)

We observe thus that according to the results, we have a total distance at the base of 59,25 cm, the first measurement was carried out at a distance of 45.57 cm and the second at 36.02 cm. The final calculated speed is 9.55 cm/s. And by obtaining the speed of the vehicle, that allowed us to obtain the time that the vehicle will take to exceed the safety distance put (here 30cm). So we will wait 3 seconds before the warning message appears.

![sensor distance result](https://user-images.githubusercontent.com/73825898/171687028-6888728b-8624-4e28-9922-cfdfc2a8168d.png)

