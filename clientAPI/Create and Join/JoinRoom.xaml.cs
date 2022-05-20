﻿using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using clientAPI.Create_and_Join;
using clientAPI.Game;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private List<Room> rooms;
        
        public JoinRoom()
        {
            
            InitializeComponent();
            this.rooms = getRooms();
            //maybe check here if rooms isnt empty
            
            showActiveRooms();
        }

        
        private void clickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu(MainProgram.MainUsername);
            menu.Show();
        }

        
        private void showActiveRooms()
        {
            foreach(Room room in this.rooms)
            {
                if(room.Metadata.IsActive==true)
                {
                    string fullRoom = room.Metadata.Name;
                    if (roomsList.Items.Contains(fullRoom)==false)
                    {
                        
                        roomsList.Items.Add(fullRoom);
                    }
                    
                }
                
            }
        }

        

        private List<Room> getRooms()
        {
            

            MainProgram.appClient.sender("", Requests.GET_ROOM_REQUEST);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            if (returnMsg.IsErrorMsg)
            {
                //Signup failed

                //MessageBox.Show("Error: Username already exists");
                MessageBox.Show(returnMsg.Message.ToString());
                return new List<Room>(); ;

            }

            GetRoomsResponse getRoomsResponse = JsonHelpers.JsonFormatDeserializer.GetRoomsResponseDeserializer(returnMsg.Message.Skip(5).ToArray());

            Console.Write(getRoomsResponse.ToString());
            
            return getRoomsResponse.Rooms;
        }

        private void clickJoin(object sender, RoutedEventArgs e)
        {
            uint id = 0;
            if (roomsList.SelectedItem != null)
            {

                
                string item= roomsList.SelectedItem.ToString();
                foreach (Room room in this.rooms)
                {
                    if (room.Metadata.Name == item)
                    {
                        id = room.Metadata.Id;
                        break;
                    }
                }
                if(id==0)
                {
                    MessageBox.Show("Selection Error!");
                }
                else
                {
                    if (sendJoinRoomRequest(id))
                    {
                        RoomData metaData = getRoomData(id);

                        WaitingRoom waitingRoom = new WaitingRoom(metaData, false);
                        waitingRoom.Show();
                        Close();
                    }
                }
               
            }
            else
            {
                
                MessageBox.Show("Selection Empty!");
            }
              
                    
        }

        private RoomData? getRoomData(uint id)
        {
            foreach (Room room in this.rooms)
            {
                if (room.Metadata.Id == id)
                {
                    return room.Metadata;
                }
            }

            return null;
        }

        private bool sendJoinRoomRequest(uint roomId)
        {
            JoinRoomRequest joinRoomRequest = new JoinRoomRequest(roomId);

            byte[] data = JsonHelpers.JsonFormatSerializer.joinRoomSerializer(joinRoomRequest);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.JOIN_ROOM_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            if (returnMsg.IsErrorMsg)
            {
                //Signup failed

                //MessageBox.Show("Error: Username already exists");
                MessageBox.Show(returnMsg.Message.ToString());
                return false;

            }

            JoinRoomResponse joinRoomResponse = JsonHelpers.JsonFormatDeserializer.JoinRoomResponseDeserializer(returnMsg.Message.Skip(5).ToArray());

            
            
            return true;
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }
    }
}
