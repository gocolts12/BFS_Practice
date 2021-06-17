# BFS_Practice
BFS graph traversal take-home assignment
Assignment:

Spacebus3000 : It’s the year 3000 and there’s a company called Spacebus that offers rides between certain spaceports. Imagine that you are given a file listing the routes that Spacebus offers. Here’s an example of what the file could look like…

Infrared Spacehub, Grand Nebula Spaceport
Blue Nova Space Market, Heavy Element Spacemine
Asteroid Research Institute, Oort Cloud Observation Facility
Infrared Spacehub, Oort Cloud Observation Facility
Oort Cloud Observation Facility, Double Ring Space Habitat

Each line means there’s a Spacebus route going back and forth between the two spaceports. In the example above, one can take a Spacebus from Asteroid Research Institute to Oort Cloud Observation Facility, and also from Oort Cloud Observation Facility to Infrared Spacehub, and also from Infrared Spacehub to Grand Nebula Spaceport. So it follows that one could travel all the way from Asteroid Research Institute to Grand Nebula Spaceport just using Spacebus. On the other hand, there is no way to get from Asteroid Research Institute to Heavy Element Spacemine using Spacebus.

Write a Java (or C++) program called “Spacebus3000” that takes three arguments - the name of a file listing Spacebus’s routes and the names of two spaceports – and outputs “yes” or “no” depending on whether one could travel from one of the spaceports to the other of the spaceports just using Spacebus. If either of the spaceport arguments isn't in the file, then the program should output "no".

Here are some sample Java interactions, assuming the example file above is named spacebusroutes.txt…

java Spacebus3000 spacebusroutes.txt “Oort Cloud Observation Facility” “Asteroid Research Institute”
> yes

java Spacebus3000 spacebusroutes.txt “Asteroid Research Institute” “Grand Nebula Spaceport”
> yes

java Spacebus3000 spacebusroutes.txt “Asteroid Research Institute” “Heavy Element Spacemine”
> no

java Spacebus3000 spacebusroutes.txt “Asteroid Research Institute” Pluto
> no

You can assume that none of the names of the spaceports will contain commas. That is, in the file, there will only be one comma on each line, separating the names of the two spaceports.

You won't need to write any code to handle the quotes that appear around the spaceport names in the example command-line interactions. The command-line environment will naturally take care of that. In the last example command-line interaction, as far as the Java method Spacebus3000.main() is concerned, args[1] is Asteroid Research Institute, and args[2] is Pluto.

There is no requirement concerning how the program should behave if the file isn't formatted as expected or if the program isn't called with the expected number of arguments.

It's best if you just send us the .java or .cpp file(s) you write, unzipped, without any .class or .exe files.



Instructions/Notes:

1) In the interest of getting this assignment back in a timely manner and to make testing easier, some sacrifices were made. Because command line arg parsing/string manipulation wasn't required (and doesn't appear to be the real point of the assignment), I kept things simple and made all spaceports in the graph one word. To test my code, please format your text file like seen below:

InfraredSpacehub,GrandNebulaSpaceport
BlueNovaSpaceMarket,HeavyElementSpacemine
AsteroidResearchInstitute,OortCloudObservationFacility
InfraredSpacehub,OortCloudObservationFacility

2) I wrote a >> override to view the adjacency lists of each node, though for some reason the text formatting on my terminal comes out weird, whereas it looks fine in Visual Studio where I developed it. Just something to be aware of. 

3) Be sure that there are no extraneous spaces at the end of each line, or any whitespace below the final line or the parsing will not work properly. 

4) Because this was done in c++, argv[0] is ./fileName and argv[1] is the name of the text file, so I had to use argv[2] and argv[3] for the spaceport name args.

5) Runtime analysis:
	-populateGraph function: 
		-Individual calls to std::vector.push_back is O(1) (amortized)
		-Individual calls to std::find on std::vector is (likely) O(n) based on the STL implementation
		-Individual calls to std::map.emplace is a log(n) operation due to a binary search in the STL implementation
		-Individual calls to std::map.find is also log(n) for the same reason
	-areConnected function:
		-O(V+E) (BFS) where V is the number of vertices and E are the number of edges
