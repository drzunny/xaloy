require("xaloy")

function plus(a,b)
	return a+b*2
end

function minus(a,b)
	return math.abs(a-b)
end

cases ={
	{name ="plus", f = plus, mode = "EQ", case={{1,2}, {3,4}}, expect={3,7}, cycle=10},
	{name ="min", f = minus , mode = "LS", case={{1,2}, {3,4}}, expect={2,2}, cycle=10}
}
tob = xaloy.create("test")
xaloy.bind(tob, cases)
xaloy.assert(tob)
xaloy.performance(tob, {1,2})
