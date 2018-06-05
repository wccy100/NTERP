package main

import (
	"JGo/JExit"
	"JGo/JHttp"
)

func exit() int {
	JHttp.Close()
	return 0
}

func initRoute() {
	JHttp.WhiteHttp("/login", Login) //登录

	JHttp.WhiteHttp("/neworder", NewOrder)               //新建订单
	JHttp.WhiteHttp("/modorder", ModOrder)               //修改订单
	JHttp.WhiteHttp("/delorder", DelOrder)               //删除订单
	JHttp.WhiteHttp("/modorderprice", ModOrderPrice)     //修改订单价格
	JHttp.WhiteHttp("/cancleorder", CancelOrder)         //取消订单
	JHttp.WhiteHttp("/produceorder", PorduceOrder)       //订单生产
	JHttp.WhiteHttp("/successorder", SuccessOrder)       //订单完成
	JHttp.WhiteHttp("/getglobalorders", GetGlobalOrders) //获取所有订单

	JHttp.WhiteHttp("/newcustomer", NewCustomer)        //新增一个客户
	JHttp.WhiteHttp("/modcustomer", ModCustomer)        //修改客户
	JHttp.WhiteHttp("/updowncustomer", UpDownCustomer)  //解约或合作客户
	JHttp.WhiteHttp("/delcustomer", DelCustomer)        //删除一个客户
	JHttp.WhiteHttp("/getallcustomers", GetAllCustomer) //获取所有客户

	JHttp.WhiteHttp("/newsupplier", NewSupplier)        //新增一个供应商
	JHttp.WhiteHttp("/modsupplier", ModSupplier)        //修改供应商
	JHttp.WhiteHttp("/updownsupplier", UpDownSupplier)  //解约或合作客户
	JHttp.WhiteHttp("/delsupplier", DelSupplier)        //删除一个供应商
	JHttp.WhiteHttp("/getallsuppliers", GetAllSupplier) //获取所有供应商

	JHttp.WhiteHttp("/newemployee", NewEmployee)           //新建一个员工
	JHttp.WhiteHttp("/modemployee", ModEmployee)           //修改员工信息
	JHttp.WhiteHttp("/outemployee", OutEmployee)           //员工离职
	JHttp.WhiteHttp("/delemployee", DelEmployee)           //删除一个员工
	JHttp.WhiteHttp("/getallemployeess", GetAllEmployeess) //获取所有的员工信息

	JHttp.WhiteHttp("/newunit", NewUnit)        //新建一个单位
	JHttp.WhiteHttp("/delunit", DelUnit)        //删除一个单位
	JHttp.WhiteHttp("/getallunits", GetAllUnit) //获取所有的单位

	JHttp.WhiteHttp("/getallmaterials", GetAllMaterial) //获取所有的物料

	JHttp.WhiteHttp("/getglobalgoods", GetGlobalGoods) //获取仓库商品
	JHttp.WhiteHttp("/newgoods", NewGoods) //新建一个商品
	JHttp.WhiteHttp("/getsuppliergoods", GetSupplierGoods) //获取供应商的物品





}

func main() {
	JExit.RegisterExitCb(exit)
	initRoute()
	JHttp.Run()
}
