// first header for simple factory pattern
class Fruit
{
	public:
		Fruit();
		virtural ~Fruit();
	public:
		virtural void show() = 0;
}

class Apple : public Fruit
{
	public:
		Apple();
		virtural ~Apple();
	public:
		virtural void show();
		
}
