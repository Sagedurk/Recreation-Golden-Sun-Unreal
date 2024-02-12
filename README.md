# Recreation Golden Sun
Recreating mechanics from *Golden Sun*, & *Golden Sun: The Lost Age* for educational purposes, to improve my skills as a game programmer.
</br>
Developed primarily with controller support in mind, in **Unreal 5.3**

Apart from the games themselves, the fandom wiki is used to quickly get information that would otherwise be a hassle to get hold of.
</br>
The information is then crosschecked against the games, to check that I have correctly implemented it.

### Challenges
* Adapting to an engine with little prior experience
* Unreal's UI system
* Wrapping my head around the many different pieces that make up the combat system
  

### Future plans
* Add features that are missing from the combat system (i.e. summons, items, combat text, status effects, etc.)
* Create a tool for easy handling of level and stat growth
* Create the basis of the overworld
* Create debug UI for overworld and combat respectively
* Including more
</br>
</br>

## COMBAT SYSTEM
I aim to create a combat system as close to Golden Sun's as I can, while also making tools that ease the creation of more generic functionalities, i.e. stat growth. </br>
The combat system has a lot of interconnected parts, such as the djinn system being connected to both the class system and summon mechanic, making it a challenge to have everything mesh together well.

### Class System
The class system can be tricky to understand. It is a system I've never grasped until I tried recreating it, even though I've replayed *Golden Sun* a number of times. </br>
For the sake of not overcomplicating to anyone unfamiliar with the franchise, there are some edge cases I am aware of but will not address here.

In order to understand the class system, an understanding of the elements is first needed. </br>
The elements are comprised of **Venus** *(Earth)*, **Mars** *(Fire)*, **Jupiter** *(Wind)*, and **Mercury** *(Water)* </br>
There are 2 different relations between the elements: *opposite*, and *symbiotic*. </br>
**Venus** & **Jupiter**, and **Mars** & **Mercury** are *opposite* </br>
**Venus** & **Mars**, and **Jupiter** & **Mercury** are *symbiotic* </br>

For the purpose of the class system, I have introduced a 3rd relation between the elements, which is the lack of a relation: *unrelated* </br>
This pairs **Venus** & **Mercury**, and **Mars** & **Jupiter**

</br>

The class an adept (playable character) is assigned, depends on the adept's innate element and the active djinn that adept has control over

Each class is part of a *class series*, which is a grouping of classes that build on each other. </br>
Each class in a *class series* has better stats and a higher djinn requirement than the one before, and sometimes new skills are acquired, depending on the class and the level of the adept. </br>


There are 3 different *class series* types: mono-elemental, dual-elemental, tri-elemental </br>

***Mono-elemental** class series* are the series adepts default to without djinn. If djinn are present, they have to be the same element as the adept. </br>
However, two adepts of the same element can have different *default series*.

***Dual-elemental** class series* require djinn of a different element, and for the best classes of the series, a few djinn of the adept element are required as well. </br>
If an adept has one djinn of each element, it is still a ***dual-elemental** class series*, and the series chosen is based on the element relations. </br>
The priority of the relations is as following: 1. *unrelated*, 2. *opposite*, 3. *symbiotic*. If a Venus adept has one djinn of each element, **Mercury** will take priority over **Jupiter** and **Mars**.

***Tri-elemental** class series* require djinn of two elements, at least 3 djinn of each, that both differ from the adept element. </br> 
The classes from these series are among the strongest classes, but they are also not available until the later portions of each game. </br>
In contrast, the ***mono-elemental*** and ***dual-elemental** class series* are available very early on.

***Tri-elemental** series* take priority over ***dual-elemental** series*, since a ***dual-elemental** series* have the requirements met at the same time as a ***Tri-elemental** series*.

</br>
</br>

## Miscellaneous

### CREDITS
This project contains copyrighted material the use of which has not always been specifically authorized by the copyrighted owner
</br>
I am in no way affiliated with *Camelot Software Planning* or *Nintendo*
</br>
This project is for educational purposes only
</br>
https://www.copyright.gov/title17/92chap1.html#107


</br>
</br>
</br>

### No license provided
