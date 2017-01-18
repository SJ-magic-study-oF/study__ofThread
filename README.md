#study__ofThread

##環境
*	OS X El Capitan(10.11.6)
*	Xcode : 7.2
*	oF : 0.9.0

##add on

##Contents
mainとAudioでmemoryを共有する際、  
これらは別threadで動作しているわけだから、  
新たに作成された別のtheadを介して渡さないとcrashの可能性があると思った。  


##検討
本sampleにて、  
	key:0  
	key:1  
を素早くpushした時のoutputは以下の通り  
	0							press 0 @ main  
	  
	b_ThreadFuncFrom_AudioIn	audioIn  
	func_0:In					audioInから呼び出したthread側の関数  
	1							press 1 @ main  
								...audioIn()にてlock中なので"1"を押したが、待たされる: MyThread.lock();  
		  
	func_0:Out  
	
	func_1:In					func_0()を抜け、unlock()されたので、main()側のlock()が入り、func_1()の実行へ  
	func_1:Out  

##注意
MY_THREAD::func_0()にてsleep()としている所を  
keyboard入力によるstep実行にした場合、  
待ち時間が長すぎるのか、appが固まってしまった(Crashした訳ではない)  

##結論
main/Audio でmemoryを共有する場合は、これをclassにまとめ、ofThreadを継承した上で、  
	lock(); access(); unlock();  
でOK.  

最初、mainとaudioでaccess先を別に用意して、thread内でCopy....  
などと複雑なこと考えていたけど、  
lock()中はaccess来ないので、もっと単純で大丈夫。  







