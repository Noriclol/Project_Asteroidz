# Asteroids Benchmarking

I have created a version of asteroids that runs with SDL2 and i will be profiling it with the inbuilt Visual studio 2022 profiler. 

### initial profiling

after running the profiler on my project it would appear that alot of it seems to be external calls.

note: all of these first benchmarkings are from the first test

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - \[External Call\]
        ntdll.dll!0x00007ffbc4c826b1|14083 \(100.00%\)|9212 \(65.41%\)|ntdll|

the remainder of the functions that i found that are heavy are mainly the collisions. I think the collisions being so heavy are because of the fact that we run alot of asteroids on a small area. causing alot of collision triggers to happen everywhere. i suspect this will only get more intense when i run more and more asteroids.

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Engine::CheckCollisions|2685 \(19.07%\)|246 \(1.75%\)|asteroidz|
|\| - Rigidbody::IsColliding|1031 \(7.32%\)|851 \(6.04%\)|asteroidz|

in the interest of data collection i will collect the isColliding function as well to check what the performance hit will be.

i will focus on optimizing the drawing of the asteroids as i already have an optimization in mind that i want to test out.

## General Sampling
### Sampling 1

as a performance test i will spawn a specified amount of asteroids in the starting wave.
the amounts will be 100, 500, 1000 asteroids respectively.

100 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw #1 |328 \(2.33%\)|37 \(0.26%\)|asteroidz|
|\| - Asteroid::Draw #2 |406 \(1.95%\)|42 \(0.20%\)|asteroidz|
|\| - Asteroid::Draw #3 |240 \(2.07%\)|28 \(0.24%\)|asteroidz|
|\| - Asteroid::Draw #4 |484 \(2.96%\)|61 \(0.37%\)|asteroidz|
|\| - Asteroid::Draw #5 |509 \(2.83%\)|56 \(0.31%\)|asteroidz|
|\| - Rigidbody::IsColliding #1 |1031 \(7.32%\)|851 \(6.04%\)|asteroidz|
|\| - Rigidbody::IsColliding #2 |1348 \(6.48%\)|1111 \(5.34%\)|asteroidz|
|\| - Rigidbody::IsColliding #3 |768 \(6.62%\)|644 \(5.55%\)|asteroidz|
|\| - Rigidbody::IsColliding #4 |1607 \(9.83%\)|1324 \(8.10%\)|asteroidz|
|\| - Rigidbody::IsColliding #5 |1602 \(8.90%\)|1331 \(7.39%\)|asteroidz|

500 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|Category|
|-|-|-|-|-|
|\| - Engine::Draw #1 |92 \(1.26%\)|0 \(0.00%\)|asteroidz|
|\| - Asteroid::Draw #2 |143 \(1.09%\)|18 \(0.14%\)|asteroidz|
|\| - Asteroid::Draw #3 |79 \(0.82%\)|8 \(0.08%\)|asteroidz|
|\| - Asteroid::Draw #4 |74 \(1.18%\)|11 \(0.18%\)|asteroidz|
|\| - Asteroid::Draw #5 |141 \(1.47%\)|23 \(0.24%\)|asteroidz|
|\| - Rigidbody::IsColliding #1|1993 \(27.21%\)|1704 \(23.26%\)|asteroidz||
|\| - Rigidbody::IsColliding #2 |2934 \(22.33%\)|2497 \(19.01%\)|asteroidz|
|\| - Rigidbody::IsColliding #3 |1719 \(17.74%\)|1462 \(15.08%\)|asteroidz|
|\| - Rigidbody::IsColliding #4 |1899 \(30.40%\)|1625 \(26.01%\)|asteroidz|
|\| - Rigidbody::IsColliding #5 |2891 \(30.23%\)|2472 \(25.85%\)|asteroidz|

1000 asteroids (only ran 3)

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw #1 |56 \(0.55%\)|8 \(0.08%\)|asteroidz|
|\| - Asteroid::Draw #2 |24 \(0.41%\)|4 \(0.07%\)|asteroidz|
|\| - Asteroid::Draw #3 |89 \(0.85%\)|14 \(0.13%\)|asteroidz|
|\| - Asteroid::Draw #4 |58 \(0.64%\)|8 \(0.09%\)|asteroidz|
|\| - Asteroid::Draw #5 |91 \(0.93%\)|12 \(0.12%\)|asteroidz|
|\| - Rigidbody::IsColliding #1 |2919 \(28.79%\)|2556 \(25.21%\)|asteroidz|
|\| - Rigidbody::IsColliding #2 |1195 \(20.44%\)|1018 \(17.41%\)|asteroidz|
|\| - Rigidbody::IsColliding #3 |3640 \(34.95%\)|3084 \(29.61%\)|asteroidz|
|\| - Rigidbody::IsColliding #4 |2212 \(24.25%\)|1877 \(20.58%\)|asteroidz|
|\| - Rigidbody::IsColliding #5 |3423 \(35.13%\)|2881 \(29.57%\)|asteroidz|

### average

|average [100 asteroids]|Total CPU |Self CPU|Module|
|-|-|-|-|
|\| - Asteroid::Draw|393.4|44.8|asteroidz|
|\| - Rigidbody::IsColliding |983.2|1,052.2|asteroidz|

|average [500 asteroids]|Total CPU |Self CPU|Module|
|-|-|-|-|
|\| - Asteroid::Draw|105.8|12|asteroidz|
|\| - Rigidbody::IsColliding |2287.2|1952|asteroidz|

|average [1000 asteroids]|Total CPU |Self CPU|Module|
|-|-|-|-|
|\| - Asteroid::Draw|63.6|9.2|asteroidz|
|\| - Rigidbody::IsColliding |2677.8|2283.2|asteroidz|

my conclusion from this data would be that since more and more performance is put on the collisions there are less samples being taken from the draw function. as it does not make sense that the drawing will be simpler the more asteroids im trying to render.

## Drawing Optimisation

### Initial Sampling

to try to account for this i will disable collisions for all gameobjects in the scene. this should remove the biggest strain on the running loop and allow me to view the render performance hit more clearly.

500 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw|4123 \(17.48%\)|429 \(1.82%\)|asteroidz|
|\| - Asteroid::Draw|3756 \(18.11%\)|415 \(2.00%\)|asteroidz|
|\| - Asteroid::Draw|4632 \(17.59%\)|490 \(1.86%\)|asteroidz|

1000 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw|2043 \(25.16%\)|205 \(2.52%\)|asteroidz|
|\| - Asteroid::Draw|4374 \(24.13%\)|465 \(2.56%\)|asteroidz|
|\| - Asteroid::Draw|4968 \(24.50%\)|550 \(2.71%\)|asteroidz|

2000 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw|2152 \(30.09%\)|234 \(3.27%\)|asteroidz|
|\| - Asteroid::Draw|5876 \(30.84%\)|650 \(3.41%\)|asteroidz|
|\| - Asteroid::Draw|5725 \(29.53%\)|639 \(3.30%\)|asteroidz|


### Optimisation

so my plan to optimise the asteroid draw function is to use a shared pointer for the texture instead of a regular pointer. im hoping this will speed up the resource fetching for the amount of asteroids

after the implementation of the pointer these are the data samples i have collected

2000 asteroids

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Asteroid::Draw|6090 \(32.54%\)|675 \(3.61%\)|asteroidz|
|\| - Asteroid::Draw|5973 \(33.26%\)|669 \(3.72%\)|asteroidz|
|\| - Asteroid::Draw|4141 \(30.55%\)|500 \(3.69%\)|asteroidz|


if this data is anything to go by i guess this means that the shared pointer was slightly worse than having a regular pointer.


## Collision Optimisation

since trying to update the drawing ended up being a dud i will fall back on trying to optimize the collisions.
the current colliding function for the rigidbodies is already quite efficient.
- it avoids using a square root to calculate the actual distance.
- it uses int calculations of the return however the vectors are floats. this creates some overhead however it should be fine.

i want to try to optimize it by:
- setting the function to be inline
- including an early exit so that if they are too far apart to collide, the function will abort.
	(this method gives a net positive if there are more objects not colliding than there are colliding)

for testing the colliders i will run with 200 asteroids in the play area. this amount gives plenty of collisions without the asteroids starting to overlap due to lack of space.

#### Before optimization:

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Rigidbody::IsColliding|3208 \(22.70%\)|2709 \(19.17%\)|asteroidz|
|\| - Rigidbody::IsColliding|3334 \(21.77%\)|2834 \(18.50%\)|asteroidz|
|\| - Rigidbody::IsColliding|3780 \(19.66%\)|3211 \(16.70%\)|asteroidz|


#### after declaring IsColliding Inline:

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Rigidbody::IsColliding|2452 \(20.98%\)|2044 \(17.49%\)|asteroidz|
|\| - Rigidbody::IsColliding|2347 \(20.37%\)|1924 \(16.70%\)|asteroidz|
|\| - Rigidbody::IsColliding|2297 \(20.23%\)|1925 \(16.95%\)|asteroidz|

note: so it would seem declaring iscolliding to be inline didnt do shit. im thinking this could be due to the compiler already setting the function to inline as it gets run so frequently, as modern compilers sometimes do...

to avoid unnessesary overhead im making the variables in the function into floats instead. as converting the floating point values from the vector2 into ints as it was before seems like an unneccesary type convertion

#### using floats instead of int:

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Rigidbody::IsColliding|2264 \(19.99%\)|1874 \(16.55%\)|asteroidz|
|\| - Rigidbody::IsColliding|2320 \(20.12%\)|1913 \(16.59%\)|asteroidz|
|\| - Rigidbody::IsColliding|2329 \(20.05%\)|1963 \(16.90%\)|asteroidz|

if anything this was a very neglible change in performance. but its not running worse so i guess thats something.
#### inline + floats + early quit from function:

|Function Name|Total CPU \[unit, %\]|Self CPU \[unit, %\]|Module|
|-|-|-|-|
|\| - Rigidbody::IsColliding|5037 \(23.23%\)|1628 \(7.51%\)|asteroidz|
|\| - Rigidbody::IsColliding|6839 \(29.06%\)|2197 \(9.34%\)|asteroidz|
|\| - Rigidbody::IsColliding|4117 \(36.25%\)|1290 \(11.36%\)|asteroidz|

so it would seem adding 2 abs() functions didnt do anything but slow the collision check down. in the profiler it would seem that 25% of the function time is spent on that one check. i guess its not worth having an early exit in this case.

### Conclusion

So after attempting to optimise 2 areas of my game the only slightly tangable improvement would be the removal of unessesary convertions in the collider function. with that said the IsColliding function is already efficient and implementing a shared pointer for the textures of the asteroid looks good on paper i suppose.  also using the Visual studio profiler for the first time and learning to use it as a tool to measure my code and look for bottlenecks was interesting. Maybe the real optimisation was the knowledge i picked up along the way..
