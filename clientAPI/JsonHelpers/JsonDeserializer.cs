using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clientAPI.Requests_and_Responses;
using System.Text.Json;


//APPLIES FOR ALL DESRIALIZER FUNCTIONS: simply uses the json data received from the server and turns it to readable data, and then sends it to matching functions.

namespace clientAPI.JsonHelpers
{
    
    internal class JsonFormatDeserializer
    {
        //byte[0] - code, byte[1,2,3,4] - length, rest = jsonstring
        public static LoginResponse loginResponseDeserializer(byte[] buffer)
        {
            

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
            

            LoginResponse response = JsonSerializer.Deserialize<LoginResponse>(jsonString);

            return response;
        }

        public static SignUpResponse signUpResponseDeserializer(byte[] buffer)
        {
            

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
           
            
            SignUpResponse response = JsonSerializer.Deserialize<SignUpResponse>(jsonString);

            return response;
        }

        public static ErrorResponse? ErrorResponseDeserializer(byte[] buffer)
        {
           

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
         

            ErrorResponse? response = JsonSerializer.Deserialize<ErrorResponse>(jsonString);

            return response;
        }

        public static LogOutResponse? LogOutResponseDeserializer(byte[] buffer)
        {
            

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
           

            LogOutResponse? response = JsonSerializer.Deserialize<LogOutResponse>(jsonString);

            return response;
        }

        public static GetRoomsResponse? GetRoomsResponseDeserializer(byte[] buffer)
        {

            
            string jsonString = System.Text.Encoding.Default.GetString(buffer);


            GetRoomsResponse? response = JsonSerializer.Deserialize<GetRoomsResponse>(jsonString);

            if(response == null)
            {
                return new GetRoomsResponse(new List<Create_and_Join.Room>(), Response.status_error);
            }

            return response;
        }

        public static GetPlayersInRoomResponse GetPlayersInRoomResponseDeserializer(byte[] buffer)
        {
          

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
           

            GetPlayersInRoomResponse? response = JsonSerializer.Deserialize<GetPlayersInRoomResponse>(jsonString);
            if(response == null)
            {
                throw new Exception("Jsonn error");
            }
            return response;
        }

        public static GetHighScoreResponse? GetHighScoreResponseDeserializer(byte[] buffer)
        {


            string jsonString = System.Text.Encoding.Default.GetString(buffer);


            GetHighScoreResponse? response = JsonSerializer.Deserialize<GetHighScoreResponse>(jsonString);

            return response;    
        }

        public static GetPersonalStatsResponse? GetPersonalStatsResponseDeserializer(byte[] buffer)
        {


            string jsonString = System.Text.Encoding.Default.GetString(buffer);


            GetPersonalStatsResponse? response = JsonSerializer.Deserialize<GetPersonalStatsResponse>(jsonString);

            return response;
        }

        public static JoinRoomResponse? JoinRoomResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            JoinRoomResponse? response = JsonSerializer.Deserialize<JoinRoomResponse>(jsonString);

            return response;
        }

        public static CreateRoomResponse? CreateRoomResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            CreateRoomResponse? response = JsonSerializer.Deserialize<CreateRoomResponse>(jsonString);

            return response;
        }
        public static LeaveRoomResponse? LeaveRoomResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            LeaveRoomResponse? response = JsonSerializer.Deserialize<LeaveRoomResponse>(jsonString);

            return response;
        }
        public static CloseRoomResponse? CloseRoomResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            CloseRoomResponse? response = JsonSerializer.Deserialize<CloseRoomResponse>(jsonString);

            return response;
        }
        public static StartGameResponse? StartGameResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            StartGameResponse? response = JsonSerializer.Deserialize<StartGameResponse>(jsonString);

            return response;
        }
        public static GetRoomStateResponse? GetRoomStateResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            GetRoomStateResponse? response = JsonSerializer.Deserialize<GetRoomStateResponse>(jsonString);

            return response;
        }

        public static LeaveGameResponse? LeaveGameResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            LeaveGameResponse? response = JsonSerializer.Deserialize<LeaveGameResponse>(jsonString);

            return response;
        }

        public static GetQuestionResponse? GetQuestionResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);

            
            TemporaryGetQuestionResponse? response = JsonSerializer.Deserialize<TemporaryGetQuestionResponse>(jsonString);

            
            SortedDictionary<uint, string> dict = new SortedDictionary<uint, string>();
                                  
            uint i = 0;
            foreach (string item in response.Answers)
            {
                dict.Add(i, item);
                i++;
            }
            GetQuestionResponse getQuestionResponse = new GetQuestionResponse(response.Status, response.QuestionText, dict);
            
            return getQuestionResponse;
        }

        public static SubmitAnswerResponse? SubmitAnswerResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);


            SubmitAnswerResponse? response = JsonSerializer.Deserialize<SubmitAnswerResponse>(jsonString);

            return response;
        }

        public static GetGameResultsResponse? GetGameResultsResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);

            //"{\"Results\":[[\"shahar\",3,7,1.0]],\"Status\":2}"
            GetGameResultsResponse? response = JsonSerializer.Deserialize<GetGameResultsResponse>(jsonString);

            return response;
        }

        public static CreateQuestionResponse? createQuestionResponseDeserializer(byte[] buffer)
        {
            if (buffer == null || buffer.Length == 0)
                return null;

            string jsonString = Encoding.Default.GetString(buffer);

           
            CreateQuestionResponse? response = JsonSerializer.Deserialize<CreateQuestionResponse>(jsonString);

            return response;
        }

        public static CloseRoomResponse? CloseRoomResponseDeserializer(byte[] buffer)
        {


            string jsonString = System.Text.Encoding.Default.GetString(buffer);


            CloseRoomResponse? response = JsonSerializer.Deserialize<CloseRoomResponse>(jsonString);

            return response;
        }
    }
}
