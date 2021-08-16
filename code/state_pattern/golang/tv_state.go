package main

import "fmt"

type state interface{
	 operate();
}

type on struct {

}

func (o *on)operate(){
	fmt.Println("on operate")
}

type off struct {

}

func (o *off)operate(){
	fmt.Println("off operate")
}


func main(){
	var s state
	var onv on
	var offv off
	s = &onv
	s.operate()
	s = &offv
	s.operate()
}