codigos:
1 mover camara blah ...

class Arbotix{

  ros::ServiceClient client;
  rosserial_arduino::Test srv;

void  Arbotix(){
 ros::init(argc, argv, "test_srv");
 ros::NodeHandle n;
 client = n.serviceClient<rosserial_arduino::Test>("moverRobot");
}
  
bool pedirServicio(bla){
  srv.request.input = bla;
  if (client.call(srv)){
    ROS_INFO("Sum: %s", srv.response.output.c_str());
    return true;
  }else{
    ROS_ERROR("Failed to call service moverRobot");
    return false;
  } 
}

  moverCamara(bla){
    pedirServicio(bla);
  }

  moverRobot(bla){
    pedirServicio(bla);
  }


};
