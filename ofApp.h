/************************************************************
検討内容
	mainとAudioでmemoryを共有する際、
	これらは別threadで動作しているわけだから、
	新たに作成された別のtheadを介して渡さないとcrashの可能性があると思った。

検討
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

注意
	MY_THREAD::func_0()にてsleep()としている所を
	keyboard入力によるstep実行にした場合、
	待ち時間が長すぎるのか、appが固まってしまった(Crashした訳ではない)

結論
	main/Audio でmemoryを共有する場合は、これをclassにまとめ、ofThreadを継承した上で、
		lock(); access(); unlock();
	でOK.
	
	最初、mainとaudioでaccess先を別に用意して、thread内でCopy....
	などと複雑なこと考えていたけど、
	lock()中はaccess来ないので、もっと単純で大丈夫。
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class MY_THREAD : public ofThread{
private:
	/****************************************
	****************************************/
	enum{
		THREAD_SLEEP_MS = 1,
		
		FUNC_WAIT_TIME = 2000,
	};
	
	
public:
	/****************************************
	****************************************/
	void threadedFunction(){
		while(isThreadRunning()) {
			lock();
			
			unlock();
			
			sleep(THREAD_SLEEP_MS);
		}
    }
	
	void func_0() { printf("%s:In\n", __FUNCTION__); sleep(FUNC_WAIT_TIME); printf("%s:Out\n", __FUNCTION__); }
	void func_1() { printf("%s:In\n", __FUNCTION__); sleep(FUNC_WAIT_TIME); printf("%s:Out\n", __FUNCTION__); }
};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
public:
	/****************************************
	****************************************/
	enum{
		WIDTH = 400,
		HEIGHT = 400,
	};
	enum{
		AUDIO_BUF_SIZE = 1024,
		AUDIO_BUFFERS = 2,
		AUDIO_SAMPLERATE = 44100,
	};

	/****************************************
	****************************************/
	int soundStream_DeviceId;
	ofSoundStream soundStream;
	
	MY_THREAD MyThread;
	
	bool b_ThreadFuncFrom_AudioIn;
	
public:
	/****************************************
	****************************************/
	ofApp(int _soundStream_DeviceId);
	~ofApp();
	
	void setup();
	void update();
	void draw();
	
	void exit();
	
	void audioIn(float *input, int bufferSize, int nChannels);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
