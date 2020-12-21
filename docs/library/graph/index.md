# alolang库:图

* 数据结构类型：图

声明：Graph(变量类型) 变量名 ;

Graph类中包含两个结构体数组point和side,分别表示点和边。

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
}
```





Graph类中包含的函数如下:

	num_of_points()是用来表示图的顶点的数目的值
	
	side_add(int x0,int y0) -> void 表示在图中第x0和第y0个点间加一条边
	side_del(int x0,int y0) ->void 表示将图中第x0和第y0个点间的边去除
	addPoint_n(point i) ->void 表示添加一个坐标为i的点
	delPoint(point i) ->void 表示删除坐标为i的点
	delPoint(int i) ->void 表示删除第i个点
	
	operator && (agraph your_graph1) ->Graph表示将两个图的边集合取交集，顶点数按最大的计算
	operator || (agraph your_graph1) ->Graph表示将两个图的边集合取并集，顶点数按最大的计算
	operator ！ () -> Graph表示将一个图取补
	
	get_num_of_points() -> int 返回顶点数目
	get_num_of_sides() -> int 返回边的数目
	is_connected() -> bool 返回是否为连通图
	is_completed() -> bool 返回是否为完全图
	circle_existed() -> bool 返回是否成环
	max_completed_part() -> int 返回最大完全图的顶点数
# TODO

