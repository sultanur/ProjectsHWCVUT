module top (	input         clk, reset,
		output [31:0] data_to_mem, address_to_mem,
		output        write_enable);

	wire [31:0] pc, instruction, data_from_mem;

	inst_mem  imem(pc[7:2], instruction);
	data_mem  dmem(clk, write_enable, address_to_mem, data_to_mem, data_from_mem);
	processor CPU(clk, reset, pc, instruction, write_enable, address_to_mem, data_to_mem, data_from_mem);
endmodule

//-------------------------------------------------------------------
module data_mem (input clk, we,
		 input  [31:0] address, wd,
		 output [31:0] rd);

	reg [31:0] RAM[63:0];

	initial begin
		$readmemh ("Sultanalieva_Nuray_data.hex",RAM,0,63);
	end

	assign rd=RAM[address[31:2]]; // word aligned

	always @ (posedge clk)
		if (we)
			RAM[address[31:2]]<=wd;
endmodule

//-------------------------------------------------------------------
module inst_mem (input  [5:0]  address,
		 output [31:0] rd);

	reg [31:0] RAM[63:0];
	initial begin
		$readmemh ("Sultanalieva_Nuray_prog1.hex",RAM,0,63);
	end
	assign rd=RAM[address]; 
endmodule

//-------------------------------------------------------------------
module processor( input         clk, reset,
                  output [31:0] PC,
                  input  [31:0] instruction,
                  output        WE,
                  output [31:0] address_to_mem,
                  output [31:0] data_to_mem,
                  input  [31:0] data_from_mem);
                
    //... write your code here ...
wire [3:00] ALUControl;
wire PCSrsJal, PCSrcJr, RegWrite, MemToReg, MemWrite, ALUSrc, RegDst, Branch;
	Control_Unit control_unit (instruction [31:26],instruction [5:00], instruction [10:6], PCSrsJal, PCSrcJr, RegWrite, MemToReg, MemWrite, ALUSrc, RegDst, Branch, ALUControl);

wire [4:0] WriteReg;
wire [4:0] A3;
wire [4:0] number = 31;
	Mux_PCSrcJal1 mux_PCSrcJal1(WriteReg,number,PCSrcJal, A3);

wire [31:00] ResultW;
wire [31:00] PCPlus4;
wire [31:00] WD3;	
	Mux_MemToReg mux_MemToReg (data_from_mem,address_to_mem, MemToReg,  ResultW);                                    	
	Mux_PCSrcJal2 mux_PCSrcJal2(ResultW,PCPlus4, PCSrcJal, WD3);

	Add_4bit add_4bit (PC, 4, PCPlus4);
wire PCSrcBeg;
wire [31:0] RD1;
wire [31:0] PCjal;
wire [31:00]PCBranchD;
wire [31:00] PCn;
wire [1:00] some_wire = 2'b00;	
assign PCjal = {instruction [25:00], PCPlus4[31:28], some_wire [1:00]};
	             
         Mux_Beg_Jr_Jal mux_Beg_Jr_Jal (RD1, PCjal, PCBranchD, PCPlus4,PCSrcBeg,PCSrcJr,PCSrcJal, PCn); 

	ProgCount programCounter (clk, reset, PCn, PC);
                     
	Reg_file reg_file( clk,WE3,instruction [25:21], instruction [20:16], A3, WD3,RD1,data_to_mem); 

wire [31:00] signImmD;
        Sign_extend sign_extend (instruction [15:0], signImmD);      
		       
	Mux_RegDst mux_RegDst (instruction [20:16] , instruction [15:11] , RegDst, WriteReg);     

wire [31:00] out_bit_shift;
wire [31:00] SrcB;	             
        Bit_shift bit_shift (signImmD, out_bit_shift);
		  
        Add_2bitshift add_2bitshift (out_bit_shift, PCPlus4, PCBranchD); 

	Mux_ALUSrc mux_ALUSrc (data_to_mem, signImmD, ALUSrc, SrcB);


wire zero;
	ALU alu (RD1, SrcB, ALUControl, address_to_mem, zero);
  	              
	Andd andd (Branch, zero, PCSrcBeg);
	     

	             
           
endmodule
//-----------------------------------------------------------------------
  module ProgCount (input             clk, reset,
                    input      [31:0] pc_next, 
                    output reg [31:0] pc);
   
    always @(posedge clk)
	pc = reset ? 0 : pc_next;
       
endmodule

//---------------------------------------------------------------------
                    
     
 module ALU (input  [31:00] SrcA, 
             input  [31:00] SrcB, 
             input  [3:00]  ALUControl,
             output reg [31:00] ALUResult,
             output         zero);
 
assign zero = (ALUResult == 0);            

      always @(*)
      begin	
      case (ALUControl) 
   4'b0010: ALUResult = SrcA + SrcB;
   4'b0110: ALUResult = SrcA - SrcB;
   4'b0000: ALUResult = SrcA & SrcB;
   4'b0001: ALUResult = SrcA | SrcB;
   4'b0011: ALUResult = SrcA ^ SrcB;
   4'b0111: ALUResult = (SrcA < SrcB) ? 1: 0;
   4'b1010: ALUResult = SrcB << SrcA; // sllv
   4'b1101: ALUResult = SrcA >> SrcB; // srlv
   4'b1111: ALUResult = SrcA >> SrcB; // srav   
   4'b1000: begin
	    ALUResult[7:0] =   SrcA[7:0] +   SrcB[7:0];   
	    ALUResult[15:8] =  SrcA[15:8] +  SrcB[15:8];
	    ALUResult[23:16] = SrcA[23:16] + SrcB[23:16];
	    ALUResult[31:24] = SrcA[31:24] + SrcB[31:24];
	    end
   4'b1001:begin 
		if (SrcA[7:0] + SrcB[7:0] >= 255) ALUResult[7:0] = 255;
		else if (SrcA[15:8] + SrcB[15:8] >= 255) ALUResult[15:8] = 255;
	 	else if (SrcA[23:16] + SrcB[23:16] >= 255)  ALUResult[23:16] = 255;
	 	else if (SrcA[31:24] + SrcB[31:24] >= 255) ALUResult[31:24] =255;
           end
   
      endcase
    end

             
 endmodule
 
 //--------------------------------------------------------------------
             
 module Control_Unit (input  [5:00] Opcode,
                      input  [5:00] Funct,
                      input  [4:00] Shamt,                   
                      output        PCSrsJal, PCSrcJr, RegWrite, MemToReg, MemWrite, ALUSrc, RegDst, Branch,
		      output [3:00] ALUControl);
 
 
wire [1:00] ALUOp;   
             
main_decoder md (Opcode, ALUOp, PCSrsJal, PCSrcJr, RegWrite, MemToReg, MemWrite, ALUSrc, RegDst, Branch);
                 
                 

 
         
ALU_op_decoder Aod (Funct, 
                    Shamt,
                    ALUOp,
                    ALUControl);
                                                                                                          
 endmodule            
 
//------------------------------------------------------------------------

module main_decoder (input  [5:00] Opcode, 
                     output reg [1:00] ALUOp,
                     output  reg   PCSrsJal, PCSrcJr, RegWrite, MemToReg, MemWrite, ALUSrc, RegDst, Branch);

   always @(*)
   begin 
   case (Opcode)
 6'b000000: 
      begin
	RegWrite = 1;
        RegDst =   1;
	ALUSrc =   0;
	ALUOp =   10;
	Branch =   0;
	MemWrite = 0;
	MemToReg = 0;
	PCSrsJal = 0;
	PCSrcJr  = 0;
      end
  6'b100011:
      begin
        RegWrite = 1;
        RegDst =   0;
	ALUSrc =   1;
	ALUOp =   00;
	Branch =   0;
	MemWrite = 0;
	MemToReg = 1;
	PCSrsJal = 0;
	PCSrcJr  = 0;
      end
   6'b101011:
      begin
	RegWrite = 0;
	ALUSrc =   1;
	ALUOp =   00;
	Branch =   0;
	MemWrite = 1;
	PCSrsJal = 0;
	PCSrcJr  = 0;
     end
  6'b000100:
     begin
	RegWrite = 0;
	ALUSrc =   0;
	ALUOp =   01;
	Branch =   1;
	MemWrite = 0;
	PCSrsJal = 0;
	PCSrcJr  = 0;
     end
  6'b001000: 
    begin
        RegWrite = 1;
        RegDst =   0;
	ALUSrc =   1;
	ALUOp =   00;
	Branch =   0;
	MemWrite = 0;
	MemToReg = 0;
	PCSrsJal = 0;
	PCSrcJr  = 0;
     end
  6'b000011:
     begin
	RegWrite = 1;
	MemWrite = 0;
	PCSrsJal = 1;
	PCSrcJr  = 0;
     end
  6'b000111:
     begin
	RegWrite = 0;
	MemWrite = 0;
	PCSrsJal = 0;
	PCSrcJr  = 1;
    end
  6'b011111:	
    begin
	RegWrite = 1;
        RegDst =   1;
	ALUSrc =   0;
	ALUOp =   11;
	Branch =   0;
	MemWrite = 0;
	MemToReg = 0;
	PCSrsJal = 0;
	PCSrcJr  = 0;
     end
   6'b000010:  // j
     begin
	RegWrite = 0;
	MemWrite = 0;
	
     end

 endcase

 end

endmodule

//--------------------------------------------------------------------

module ALU_op_decoder  (input  [5:00]     Funct, 
                 	input  [4:00]     Shamt,
                        input  [1:00]     ALUOp,
                        output reg [3:00] ALUControl );

always @(*)
   begin 
   case (ALUOp)
2'b00:
	ALUControl = 4'b0010;
2'b01:
	ALUControl = 4'b0110;
2'b10: begin        
   	if (Funct == 6'b100000)
	    ALUControl = 4'b0010;

	else if (Funct == 6'b100010)
	         ALUControl = 4'b0110;

	else if (Funct == 6'b100100)
	         ALUControl = 4'b0000;

	else if (Funct == 6'b100101)
	         ALUControl = 4'b0001;

	else if (Funct == 6'b101010)
	         ALUControl = 4'b0111;

	else if (Funct == 6'b000100)
	         ALUControl = 4'b1010; // sllv

	else if (Funct == 6'b000110)
	         ALUControl = 4'b1101; // srlv

	else if (Funct == 6'b000111)
	         ALUControl = 4'b1111; // srav
        end

2'b11: begin 
	 if (Funct == 6'b010000 && Shamt == 5'b00000)
	     ALUControl = 4'b1000;
	 else if (Funct == 6'b010000 && Shamt == 5'b00100)
	          ALUControl = 4'b0100;
        end
  
   endcase 

  end

endmodule	

//----------------------------------------------------------------


module Sign_extend (input [15:0] sign_ext_input, 
		    output[31:0] sign__ext_output);

    assign sign_ext_output = { {16{sign_ext_input[15]}}, sign_ext_input[15:0]};

endmodule

//-----------------------------------------------------------------
 module Mux_RegDst ( input [4:00] Rt,
	             input [4:00] Rd,
                     input RegDst,
	             output reg [4:00] out_mux_RegDst);
always@ (*)
     out_mux_RegDst = RegDst? Rd: Rt; 


endmodule

//------------------------------------------------------------------

module Mux_PCSrcJal1 (input [4:00]      inp_mux_out_mux_RegDst,
	              input [4:00]      inp_mux31,
                      input             PCSrcJal,
	              output reg [4:00] out_mux_PCSrcJal1);

   always@ (*)
    out_mux_PCSrcJal1 = PCSrcJal ? inp_mux31: inp_mux_out_mux_RegDst; 


endmodule

//--------------------------------------------------------------------

module Mux_PCSrcJal2 ( input  [31:00]     inp_mux_out_MemToReg,
	    	       input  [31:00]     inp_zero_from_bigmux,
                       input              PCSrcJal,
	               output reg [31:00] out_mux_PCSrcJal2);
     always@ (*)    
     out_mux_PCSrcJal2 = PCSrcJal ? inp_zero_from_bigmux: inp_mux_out_MemToReg;


endmodule

//-------------------------------------------------------------------

module Mux_ALUSrc ( input [31:00]      RD2, 
	            input [31:00]      input_muxALUSrc_sign__ext_output,
                    input              ALUSrc,
	            output reg [31:00] out_muxALUSrc_SrcB);
always@ (*)
      out_muxALUSrc_SrcB = ALUSrc? input_muxALUSrc_sign__ext_output: RD2;

endmodule
//------------------------------------------------------------------

module Mux_MemToReg ( input  [31:00] inp_mux_rd,
	              input  [31:00] inp_mux_ALUResult,
                      input    MemToReg,
	              output [31:00] out_MemToReg);

     assign out_MemToReg = MemToReg? inp_mux_rd: inp_mux_ALUResult;

endmodule

//----------------------------------------------------------------------

module Bit_shift (input [31:00] in_bit_shift,
		  output reg [31:00] out_bit_shift);
  always@ (*)
     out_bit_shift = in_bit_shift << 2;

endmodule

//-------------------------------------------------------------------
		 
module Andd (input  one,
	     input  second,
	     output res_and);

    assign res_and = one & second;

endmodule


//----------------------------------------------------------------------
module Mux_Beg_Jr_Jal (input[31:00]       jr, 
		       input[31:00]       jal,
		       input[31:00]       beg, 
		       input[31:00]       zero,
		       input              PCSrcBeg,
		       input              PCSrcJr,
		       input              PCSrcJal,
		       output reg [31:00] out_muxBegJrJal);

always@(*)
 begin
        if(PCSrcBeg) out_muxBegJrJal = beg; 
	else if (PCSrcJr) out_muxBegJrJal = jr;
	else if (PCSrcJal) out_muxBegJrJal = jal;
	else out_muxBegJrJal = zero;
end
 

endmodule

//-----------------------------------------------------------------------
module  Add_4bit (input  [31:00] inp_add4bit_pc, 
		  input  [31:00] constant_b,           
                  output reg [31:00] out_add_4bit);
                    
always @(*)
    
    out_add_4bit = inp_add4bit_pc + constant_b;
   
endmodule


//----------------------------------------------------------

module Add_2bitshift (input [31:00] PCPlus4,
	              input [31:00] inp_add_2bitshift_out_bit_shift,
	              output reg [31:00] PCBranch);

always @(*)

      PCBranch = PCPlus4 + inp_add_2bitshift_out_bit_shift;
  
endmodule


//------------------------------------------------------------

module Reg_file (input         clk,WE3,
                 input [4:00]  A1,
	         input [4:00]  A2,
		 input [4:00]  A3,
	         input [31:00] WD3,
	         output[31:00] RD1,
		 output[31:00] RD2);

    reg[31:0] reg_array[31:0]; // array of 32 bit long registers
	
assign RD1 = A1? reg_array[A1] : 0;
assign RD2 = A2? reg_array[A2] : 0;

   always @(posedge clk)
       begin 
	if (WE3)
 		begin 
		 reg_array[A3] =WD3;
		end
	end
  

endmodule

//-----------------------------------------------------------




        
             
             
             
             
                           
                     
