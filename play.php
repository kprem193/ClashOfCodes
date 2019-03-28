<html>
<head>

	<link rel="stylesheet" type="text/css" href="css/index.css" />
</head>
<body>

<script src="js/jquery.js"></script>
<script >
	$(function(){

	});
</script>

</body>
</html>
<?php
session_start();
require_once('connect_algodb.php');
//require_once('countdown.php');
require_once('core.php');
$_SESSION['winner']=0;
if((isset($_SESSION['player2']))){
/*for storing moves*/
$_SESSION['wpl']=array();                 // contains sequence of moves by player 1 or 2
$_SESSION['wbox']=array();                // contains box which was selected
$_SESSION['wside']=array();               // contains the side selected
$_SESSION['nbox']=array();                // contains the number of box created in each move
/*data initialization*/
//user data
$num=$_SESSION['num'];
$userid1=$_SESSION['player1'];
$userid2=$_SESSION['player2'];
$error_msg="";
$p1_name=$fplayer1=$_SESSION['fplayer1'];
$p2_name=$fplayer2=$_SESSION['fplayer2'];
// code files
$my_file1="codes/$userid1".".c";
$my_file2="codes/$userid2".".c";
$moniter_file="codes/moniters".".cpp";
//actual files
$moniter="$num/moniter.cpp";
$p1_code="$num/p1.cpp";
$p2_code="$num/p2.cpp";
$input1="$num/input1.txt";
$input2="$num/input2.txt";
$moniter_input="$num/moniter_input.txt";
make_file('',$input1);
make_file('',$input2);
make_file('',$moniter_input);
$file_contents = file_get_contents($my_file1);
make_file($file_contents ,$p1_code);
$file_contents = file_get_contents($my_file2);
make_file($file_contents ,$p2_code);
$file_contents = file_get_contents($moniter_file);
make_file($file_contents ,$moniter);

$p1m=0;
$move=0;
//input -256 to  moniter
//save output to input1
file_put_contents($moniter_input,"-256");
$error=shell_exec("g++ -o om $moniter   2>&1");
	if(empty($error)){
		$output=shell_exec("./om < $moniter_input");
		file_put_contents($input1,$output);


		$p1_e=0;$p2_e=0;

		$error1=shell_exec("g++ -o op1 $p1_code   2>&1");
		if(!empty($error1)){
			$p1_e=1;
		}
		$error2=shell_exec("g++ -o op2 $p2_code   2>&1");
		if(!empty($error2)){
			$p2_e=1;
		}

        $winner='0';

		if($p1_e==1&&$p2_e==0){
			$error_msg = 'error in p1';
			$winner = $p2_name;

		}else if($p1_e==0&&$p2_e==1){
			$error_msg = 'error in p2';
			$winner = $p1_name;

		}else if($p1_e==1&&$p2_e==1){
			$error_msg = 'error in both';

		}else{

            $p1_box=0;
            $p2_box=0;

            $turn='1';
			//give input1 to p1_code
//append output and input1-> moniter_input
//get output and give it to input2 if number end here


			while(true){
			    if($turn=='1')
                {
                    $output1=shell_exec("./op1 < $input1");
                    if(!empty($output1)){
                        sscanf($output1, "%d %c",$x,$y);
                        echo '<hr><span class="print">'.$p1_name.' played at('.$x.','.$y.')</span>';
                        $_SESSION['wpl'][$p1m]=1;
                        $_SESSION['wbox'][$p1m]=$x;
                        $_SESSION['wside'][$p1m]=$y;
                        $p1m++;
                        $move++;

                        $file_contents = file_get_contents($input1);
                        file_put_contents($moniter_input,'1 '.$output1.' '.$file_contents);
			            //echo file_get_contents($moniter_input);
			
                        $outputm=shell_exec("./om < $moniter_input");
                        if(!empty($outputm)){

                            sscanf($outputm,"%d",$type);
                            if($type==-1){
                            //wrong move
                                $error_msg="p1 made wrong move";
                                $winner = $p2_name;
                                $_SESSION['nbox'][$p1m-1]=0;
                                break;
                            }else if($type==501){
                            //game completed and 1 box created by user
                                $_SESSION['nbox'][$p1m-1]=1;
                                $p1_box++;
                                break;
                            }else if($type==502){
                                //game completed and 2 box created by user
                                $_SESSION['nbox'][$p1m-1]=2;
                                $p1_box+=2;
                                break;
                            }else if($type==601){
                            //1 box created by user
                                $_SESSION['nbox'][$p1m-1]=1;
                                $p1_box++;

                            }else if($type==602){
                            //2 boxes crated by user
                                $_SESSION['nbox'][$p1m-1]=2;
                                $p1_box+=2;
                            }else if($type==700){
                            //nothing special happened
                                $_SESSION['nbox'][$p1m-1]=0;
                                $turn='2';
                            }
                                file_put_contents($input2,substr($outputm,4));
                            // also remove the initial number from output
                       
                        }

                    }else{
                    //no output
                        $error_msg="p1 didn't made move";
                        $winner = $p2_name;
                        break;
                    }

                 }
                 else
                 {
                    $output2=shell_exec("./op2 < $input2");
                    if(!empty($output2)){
                        sscanf($output2, "%d %c",$x,$y);
                        echo '<hr><span class="print">'.$fplayer2.' played at('.$x.','.$y.')</span>';
                        $_SESSION['wpl'][$p1m]=2;
                        $_SESSION['wbox'][$p1m]=$x;
                        $_SESSION['wside'][$p1m]=$y;
                        $p1m++;
                        $move++;

                        $file_contents = file_get_contents($input2);
                        file_put_contents($moniter_input,'2 '.$output2.' '.$file_contents);

                        $outputm=shell_exec("./om < $moniter_input");
                        if(!empty($outputm)){

                            sscanf($outputm,"%d",$type);
                            if($type==-1){
                            //wrong move
                                $error_msg="p2 made wrong move";
                                $winner = $p1_name;
                                $_SESSION['nbox'][$p1m-1]=0;
                                break;
                            }else if($type==501){
                                //game completed and 1 box created by user
                                $p2_box++;
                                $_SESSION['nbox'][$p1m-1]=1;
                                break;
                            }else if($type==502){
                                //game completed and 2 box created by user
                                $p2_box+=2;
                                $_SESSION['nbox'][$p1m-1]=2;
                                break;
                            }else if($type==601){
                                //1 box created by user
                                $_SESSION['nbox'][$p1m-1]=1;
                                $p2_box++;

                            }else if($type==602){
                                //2 boxes crated by user
                                $_SESSION['nbox'][$p1m-1]=2;
                                $p2_box+=2;
                            }else if($type==700){
                                //nothing special happened
                                $_SESSION['nbox'][$p1m-1]=0;
                                $turn='1';
                            }
                                file_put_contents($input1,substr($outputm,4));
                            // remove the initial number
                        
                        }

                    }else{
                    //no output
                        $error_msg="p2 didn't made move";
                        $winner = $p1_name;
                        break;
                    }
                 }
		
			}
            if($winner=='0'){
                if($p1_box>$p2_box)
                $winner=$p1_name;
                else if($p2_box>$p1_box)
                $winner=$p2_name;
                else
                $winner="Draw match";
            }
		}

	}else{

		//echo $error;
		$error_msg="$error Internal error in moniter";

	}
	echo $error_msg.' '.$winner;
$_SESSION['i']=-1;
$_SESSION['max']=$move-1;
$_SESSION['pp1']=-1;
$_SESSION['pp2']=-1;
$_SESSION['winner']=$winner;
echo '<span class="win-disp"><br>player '.$_SESSION['winner'].' Won the Game<a href="trial-exec.php" style="color:rgb(242, 9, 25);"><b> Wanna Play with other</b></span>';
//for animation
//redirect_to('end.php');
}
?>
