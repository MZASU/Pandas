# Pandas

## Presentation

This repo as for goal contain the implementation of multiple type of neural networks. I intend to write it myself but i'm still open to comments, however if you want to make major changes I recommend forking the repo for yourself. Reminder that you can do absolutly whatever you like with this code.

## V1

First pull on the master branch, a basic FNN work. Really nothing fancy just reads the image all layer are basic (no convolution or w/e).

If you want more info and want to understand my code, i tried to put as much explanation in comments as possible.

### Data

I built this exact program using the -O3 parameters. I then ran it over 1000000 trainings. It took 22m40s. Here is a graph of Success rate (in percent) over trials (in 1000). I'm 99% sure i didn't implement momentum correctly so i guess that's the reason i'm getting 95% correct after 1million trainings.

![data](.images/image1.png)
