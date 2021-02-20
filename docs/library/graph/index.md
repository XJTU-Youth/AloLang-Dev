# alolang库:图

* 数据结构类型：图

声明：Graph(变量类型) 变量名 ;

Graph类中包含两个结构体数组point和side,分别表示点和边，点本身是无序的，不支持根据点的序号来进行删除/添加边的操作。

```
struct point
{
	type x;
	type y;
};
struct side
{
	point a;
	point b;
};
```



Graph类中包含的函数如下:

	getPointsNum() -> int 返回点的数目
	getSidesNum() -> int 返回边的数目(带方向)
	
	//以下的四个函数可以保证安全
	addSide(point x,point y) -> bool 表示在坐标为的间加一条边为x->y，返回false为添加失败
	delSide(point x,point y) ->bool 表示删掉x->y的边，返回false为添加失败
	addPoint(point i) ->bool //表示添加一个坐标为i的点,返回false为添加失败
	delPoint(point i) ->bool //表示删除坐标为i的点,返回false为删除失败
	
	operator && (Graph x1,Graph x2) ->Graph //表示将两个图的边集合取交集，顶点数按最大的计算
	operator || (Graph x1,Graph x2) ->Graph //表示将两个图的边集合取并集，顶点数按最大的计算
	operator ! () -> Graph //表示将一个图取补
	
	isConnected() -> bool //返回是否为连通图
	isCompleted() -> bool //返回是否为完全图
	getCircleNum() -> unsigned int //返回欧拉回路的数量
	max_completed_part() -> int //返回最大完全图的顶点数
# TODO

