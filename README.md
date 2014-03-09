HTTP-Tester
======
![Http-Tester](http://dl.dropboxusercontent.com/u/22799853/Relazione%20Telematica/Main.png)


Http-Tester is a simple http requests sender written in qt. It allows you to send the four major requests of http protocol to a server and it let you analyse its response. 
During the composition of the request through gui, the program composes the related textual request in telnet style. 

It's a project for the "Telematica A" exam, course for the degree in software engineering in Parma, Italy. 

The exam report is available at this [link](http://dl.dropbox.com/u/22799853/Relazione%20Telematica/HTTP-Tester%20Relazione.pdf) in Italian language.

###DEPENDENCIES

 * Qt 4.8.5
 * Gcc
 * QMake
 * Make

###COMPILE

Go to the folder containing the source code, from console type:    

    cd ~/HTTP-Tester src    
    qmake (qmake-qt4 on some architectures like Fedora)    
    make

###RUN

Go to the folder containing the build, from console type:

    cd ~/HTTP-Tester src    
    ./HTTP-Tester

======

Idea and Design:  
Fabrizio Signoretti - fasigno37@gmail.com    
Filippo Groppi - filippo.groppi@studenti.unipr.it

This software is under GPLv3.
