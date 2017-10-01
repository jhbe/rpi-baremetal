#ifndef LED_H_
#define LED_H_

class CLed {
public:
	CLed(int gpioNumber);
	~CLed();

	void Set();
	void Clear();

private:
	int m_gpioNumber;
};

#endif /* LED_H_ */
