import os
import sys
import re

opcode_table = {"PUSH":18,"GOTO":11,"ADD":3,"SUB":4,"POP":7,"EQU":8,"GRT" : 9,"LST" : 10,"GOTO" : 11,"GOZ" : 12,"GONZ" : 13,"END" : 14,"DUP" : 15,"FLIP" : 16,"NOP" : 17,"PUSH" : 18,"GON" : 19,"GOP" : 20,"GOC" : 21,"GONC" : 22,"GONP" : 23,"ADDC" : 24,
	"ADC" : 26,
	"SBC" : 27,
	"SUBC" : 25,
	"IN" : 28,
	"OUT" : 29,
	"MOV" : 30 }
symtab = {}

def exact_match(phrase, word):
    b = r'(\s|^|$)' 
    res = re.match(b + word + b, phrase, flags=re.IGNORECASE)
    return bool(res)

def idToken(line):
	cleanup(line)
	token_exists = False
	tokens = ["READ","WRTD","ADD","SUB","MUL","DIV","POP","EQU","GRT","LST","GOTO","GOZ","GONZ","END","DUP","FLIP","NOP","PUSH","GON","GOP","GOC","GONC","GONP","ADDC","SUBC","ADC","SBC","IN","OUT","MOV" ]
	for token in tokens:
		if exact_match(line, token):
			token_exists = True
			index = line.find(token)+len(token)
			return token,index,token_exists
	return line,"",token_exists

def cleanup(s):
	s = s.strip(" ")
	s = s.strip("\n")

count = 0
with open("test.txt") as f:
	forward_reference = {}
	forward_exists = False
	out_file = open("output.txt","r+w")
	content = f.readlines()
	for line in content:
		token,index,token_exists = idToken(line)
		if token_exists == True: #not a label
			if token == "PUSH":
				operand = line[index:]
				operand = operand.rstrip("\n")
				operand = operand.strip(" ")
				out_file.write(str(opcode_table[token])+"\n")
				count+=1
				out_file.write(operand+"\n")
				count+=1
			elif "GO" in token:
				
				operand = line[index:]
				operand = operand.rstrip("\n")
				operand = operand.strip(" ")
				out_file.write(str(opcode_table[token])+"\n")
				count+=1
				print "\n",operand
				if operand.isdigit():
					out_file.write(operand+"\n")
					count+=1   #direct jump without labels.
				elif operand in symtab.iterkeys(): #back ref with goto
					print "in back ref"
					out_file.write(str(symtab[operand])+"\n")
					count+=1
				elif operand not in symtab.iterkeys(): #forward ref with goto
					print "\nno symbol added block"
					forward_exists = True
					forward_reference[token]=count
					out_file.write(operand+"\n")
					count+=1
			else:
				out_file.write(str(opcode_table[token])+"\n")
				count+=1
		else: # label
			if  index == "":
				token = token.rstrip("\n")
				print "working on label",token
				if token not in symtab.iterkeys(): 
				 #reference defintion. symbol already defined. replace it
					symtab[token] = count
					print "\nadding symbol",token,"at count :",count


	out_text = open("out_code.txt","w")
	if forward_exists:
		out_file.seek(0)
		content = out_file.readlines()
		for line in content:
			print "\n code: ",line
			line = line.strip("\n")
			line = line.strip(" ")
			if line.isalpha():
				print "\nforward ref for symbol",line," replacing with ",str(symtab[line])
				line = line.rstrip("\n")

				out_text.write(str(symtab[line])+"\n")
				continue
			out_text.write(line+"\n")
			
	out_text.close()
	out_file.close()