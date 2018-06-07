
abstract type SuperEntity end

abstract type AbstractEntity <: SuperEntity end

type Thread2Entity <: AbstractEntity
	id::Int32
	#ThreadEntity(         ) = new( 1 )
	#ThreadEntity(id       ) = ThreadEntity( Int32(id) )
end