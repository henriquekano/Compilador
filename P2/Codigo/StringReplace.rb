kvs = {}
buffer = ""
File.open("wirth_modificado.txt", "r")do |f|
  f.each_line do |line|

    buffer << line.gsub("\n", "")
    line2 = line.gsub("\n", "").gsub(" ", "")
    if line2[line2.length-1, line2.length-1] == "." then
      buffer.gsub("\n", "")
      buffer.gsub("\t", " ")
      linekv = line.split(" = ")
      kvs[linekv[0]] = linekv[1]
      buffer = ""
    end
  end
end

nterm_sub = [
"D",
"L",
"SPECIAL",
"ESPACO",
"ANY",
"ID",
"INT",
"NUM",
"TIPO",
"STRING",
"_COMPARADOR",
"COMPARADOR_BOOL",
"ATRIBUICAO", 
"_DECLARACAO", 
"CONDICIONAL", 
"ITERACAO", 
"SELECAO", 
"ENTRADA", 
"SAIDA"
]



p kvs

File.open("rules", 'w') do |file| 
  kvs.each do |key, value|
    file.write(key + " = " + value) 
  end
end

kvs.each_key do |key|
  unless nterm_sub.include? key then
    unless kvs[key].include? key
      kvs.each do |innerkey, innervalue|
        if key != innerkey
          kvs[innerkey].gsub!(/#{key}/, "(" + kvs[key].gsub("\n", "").gsub(".", "") + ")")
        end
      end
    end
  end
end

File.open("new_wirth", 'w') do |file| 
  kvs.each do |key, value|
    file.write(key + " = " + value) 
  end
end

# kvs.each do |key, value|

# end