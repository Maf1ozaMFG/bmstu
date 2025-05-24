using Core.Interfaces;
using DatabaseModels;
using System.Text.RegularExpressions;
using Group = DatabaseModels.Group;

namespace Core.Services;

public class StudentService
{
    private const int MinAge = 16;
    private const int MaxAge = 100;
    private const int MinNameLength = 2;
    private const int MaxNameLength = 50;
    private readonly IDataRepository<Student> _studentRepository;
    private readonly IDataRepository<Group> _groupRepository;

    public StudentService(IDataRepository<Student> studentRepository, IDataRepository<Group> groupRepository)
    {
        _studentRepository = studentRepository;
        _groupRepository = groupRepository;
    }

    private void ValidateAge(int age)
    {
        if (age < MinAge)
            throw new Exception($"Возраст студента не может быть меньше {MinAge} лет");
        if (age > MaxAge)
            throw new Exception($"Возраст студента не может быть больше {MaxAge} лет");
    }

    private void ValidateName(string name)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new Exception("Имя студента не может быть пустым");
            
        if (name.Length < MinNameLength)
            throw new Exception($"Имя студента должно содержать минимум {MinNameLength} символа");
            
        if (name.Length > MaxNameLength)
            throw new Exception($"Имя студента не может быть длиннее {MaxNameLength} символов");
            
        if (!Regex.IsMatch(name, @"^[а-яА-Яa-zA-Z\-\s]+$"))
            throw new Exception("Имя студента может содержать только буквы, дефис и пробелы");
    }

    public void CreateStudent(string name, int age, int groupId)
    {
        try
        {
            ValidateAge(age);
            ValidateName(name);

            var group = _groupRepository.GetById(groupId);
            if (group == null)
                throw new Exception("Cannot find group by this ID");

            var studentsInGroup = GetStudentsCountInGroup(groupId);
            if (studentsInGroup >= 30)
                throw new Exception("В группе не может быть больше 30 студентов");

            var student = new Student
            {
                Name = name,
                Age = age,
                GroupId = groupId
            };

            _studentRepository.Add(student);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void UpdateStudent(int id, string name, int age, int groupId)
    {
        try
        {
            ValidateAge(age);
            ValidateName(name);

            var student = _studentRepository.GetById(id);
            if (student == null)
                throw new Exception("Cannot find student by this ID");

            var group = _groupRepository.GetById(groupId);
            if (group == null)
                throw new Exception("Cannot find group by this ID");

            if (student.GroupId != groupId)
            {
                var studentsInGroup = GetStudentsCountInGroup(groupId);
                if (studentsInGroup >= 30)
                    throw new Exception("В группе не может быть больше 30 студентов");
            }

            student.Name = name;
            student.Age = age;
            student.GroupId = groupId;

            _studentRepository.Update(student);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public Student GetById(int id)
    {
        try
        {
            var student = _studentRepository.GetById(id);
            return student ?? throw new Exception("Cannot find student by this ID");
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public IEnumerable<Student> GetAllStudents()
    {
        try
        {
            return _studentRepository.GetAll();
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void DeleteStudentById(int id)
    {
        try
        {
            var student = new Student { Id = id };
            _studentRepository.Delete(student);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public int GetStudentsCountInGroup(int groupId)
    {
        try
        {
            return _studentRepository.GetAll().Count(s => s.GroupId == groupId);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public double GetAverageAgeInGroup(int groupId)
    {
        try
        {
            var students = _studentRepository.GetAll().Where(s => s.GroupId == groupId);
            if (!students.Any())
                throw new Exception("No students in this group");

            return students.Average(s => s.Age);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }
}
