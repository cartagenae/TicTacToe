colors = ["red", "white", "blue"]

def DisplayArray(*array)
	array.each do |element|
		puts element
	end
end

puts "\ncolor array:"
DisplayArray(colors)

someArray = [1, 2, 3]

puts "#{someArray.first} \n"

numbers = [2, 92, 49, 4, 5, 29, 882]

numbers.sort!

numbers.each do |number|
	puts number
end

puts "\nLe Logiciel a deja fini\n"

