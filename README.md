# RectangleSearch

## Description
This program finds the amount of rectangles that can be created from any given set of points. 

I got this problem from this video 
	https://youtu.be/EuPSibuIKIg 

Also, it should be noted that this solution was not entirely my idea. Parts of this solution come from the dicussion in the video listed above but I came up with a slightly different solution that I wanted to try out.

## My Approach
The programmers in video discussed a possible solution to this problem involving mathematical vectors, but I took a simpler approach and chose to look at the diagonals of rectangles. 

It is given that if two diagonals have the same midpoint and length, they form a rectangle. As such, if we consider any two given points to be a diagonal of a rectangle, we can find the amount of rectangles formed by looking for other diagonals with the same midpoint and length. We can take an approach similar to that of the one discussed in the video and create a hash map with the two properties mentioned above being the key type and an int being the value type to keep track of how many diagonals meet this property.

To avoid repitions of diagonals such as  
**Diagonal 1: (a, b) -> (c, d)  
Diagonal 2: (c, d) -> (a, b)**  
,for every point, I only form diagonals with the points that come after it in the vector. So if point (a, b) comes before (c, d), only Diagonal 1 will be formed and vice versa.

This solution has an order notation of **O(n^2)** with n being the number of points given.
