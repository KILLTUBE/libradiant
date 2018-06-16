importall Base

type Vec2
	x::Float32
	y::Float32
	function Vec2()
		new(0, 0)
	end
	function Vec2(x, y)
		new(x, y)
	end
end
zero(::Type{Vec2}) = Vec2(0, 0)
function (+)(a::Vec2, b::Vec2)::Vec2
	return Vec2(
		a.x + b.x,
		a.y + b.y
	)
end
function (-)(a::Vec2, b::Vec2)::Vec2
	return Vec2(
		a.x - b.x,
		a.y - b.y
	)
end
function (*)(a::Vec2, scalar)::Vec2
	a * Float32(scalar)
end
function (*)(a::Vec2, scalar::Float32)::Vec2
	return Vec2(
		a.x * scalar,
		a.y * scalar
	)
end

#using StaticArrays
#const Vec3 = SVector{3,Float32}
struct Vec3
	x::Float32
	y::Float32
	z::Float32
	function Vec3()
		new(0, 0, 0)
	end
	function Vec3(x, y, z)
		new(x, y, z)
	end
end
struct vec3
	x::Float32
	y::Float32
	z::Float32
end

pointer(this::Vec3) = Ptr{Float32}(pointer_from_objref(this))
convert(::Type{Vec3}, address::Ptr{Float32})::Vec3 = unsafe_load(Ptr{Vec3}(address))

function normalize(this::Vec3)::Vec3
	scale = 1 / length(this)
	return this * scale
end

iszero(vec::Vec3) = (vec.x + vec.y + vec.z) == 0.0

#lol this fucks up so much, because of the SVector stuff
#Base.length(this::Vec3) = 3
#Base.length(this::Vec3) = sqrt(this[1]*this[1] + this[2]*this[2] + this[3]*this[3])
length(this::Vec3) = sqrt(this.x*this.x + this.y*this.y + this.z*this.z)

function distanceSquared(a::Vec3, b::Vec3)::Float32
	c = b - a
	return (c.x * c.x) + (c.y * c.y) + (c.z * c.z)
end

importall Base

zero(::Type{Vec3}) = Vec3(0,0,0)

function (+)(a::Vec3, b::Vec3)::Vec3
	return Vec3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	)
end

function (-)(a::Vec3, b::Vec3)::Vec3
	return Vec3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	)
end

function (*)(a::Vec3, scalar)::Vec3
	a * Float32(scalar)
end
function (*)(a::Vec3, scalar::Float32)::Vec3
	return Vec3(
		a.x * scalar,
		a.y * scalar,
		a.z * scalar
	)
end

function distance(a::Vec3, b::Vec3)::Float32
	return sqrt(distanceSquared(a, b))
end

immutable LineSegment3
	origin::Vec3
	direction::Vec3
	LineSegment3(a::Vec3, b::Vec3) = new(a, b-a)
end

function closestPoint(this::LineSegment3, point::Vec3)::Vec3
	w = point - this.origin
	
	proj = dot(w, this.direction)

	if proj <= 0f0
		return this.origin
	else
		vsq = dot(this.direction, this.direction)
		if proj >= vsq
			return this.origin + this.direction
		else
			return this.origin + (proj/vsq) * this.direction
		end
	end
end

Vec3X(x)::Vec3 = Vec3(x, 0, 0)
Vec3Y(y)::Vec3 = Vec3(0, y, 0)
Vec3Z(z)::Vec3 = Vec3(0, 0, z)

if false
	ls = LineSegment3( pos(wp_a), pos(wp_b) )
	closest_point = closestPoint(ls, pos(player))
	pos!(go_cube, closest_point)
end


