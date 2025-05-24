using Core.DataRepositories;
using Core.Interfaces;
using Core.Services;
using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core;

public class DatabaseCore
{
    private readonly DbContext _context;

    private readonly IDataRepository<Student> _studentRepository;
    private readonly StudentService _studentService;

    private readonly IDataRepository<Group> _groupRepository;
    private readonly GroupService _groupService;

    private readonly IDataRepository<Curator> _curatorRepository;
    private readonly CuratorService _curatorService;

    public DatabaseCore(DbContext ctx)
    {
        _context = ctx;

        _studentRepository = new EntityFrameworkRepository<Student>(_context);
        _groupRepository = new EntityFrameworkRepository<Group>(_context);
        _curatorRepository = new EntityFrameworkRepository<Curator>(_context);

        _studentService = new StudentService(_studentRepository, _groupRepository);
        _groupService = new GroupService(_groupRepository);
        _curatorService = new CuratorService(_curatorRepository, _groupRepository);
    }

    // Student methods
    public void CreateStudent(string name, int age, int groupId) => _studentService.CreateStudent(name, age, groupId);
    public void UpdateStudent(int id, string name, int age, int groupId) => _studentService.UpdateStudent(id, name, age, groupId);
    public Student GetStudentById(int id) => _studentService.GetById(id);
    public IEnumerable<Student> GetAllStudents() => _studentService.GetAllStudents();
    public void DeleteStudentById(int id) => _studentService.DeleteStudentById(id);
    public int GetStudentsCountInGroup(int groupId) => _studentService.GetStudentsCountInGroup(groupId);
    public double GetAverageAgeInGroup(int groupId) => _studentService.GetAverageAgeInGroup(groupId);

    // Group methods
    public void CreateGroup(string name) => _groupService.CreateGroup(name);
    public void UpdateGroupNameById(int id, string name) => _groupService.UpdateGroupNameById(id, name);
    public void UpdateGroupCreationDateById(int id, DateTime newCreationDate) => _groupService.UpdateCreationDateById(id, newCreationDate);
    public Group GetGroupById(int id) => _groupService.GetById(id);
    public IEnumerable<Group> GetAllGroups() => _groupService.GetAllGroups();
    public void DeleteGroupById(int id) => _groupService.DeleteGroupById(id);

    // Curator methods
    public void CreateCurator(string name, string email) => _curatorService.CreateCurator(name, email);
    public void UpdateCuratorNameById(int id, string name) => _curatorService.UpdateCuratorNameById(id, name);
    public Curator GetCuratorById(int id) => _curatorService.GetById(id);
    public IEnumerable<Curator> GetAllCurators() => _curatorService.GetAllCurators();
    public void DeleteCuratorById(int id) => _curatorService.DeleteCuratorById(id);
    public string GetCuratorNameByStudentId(int studentId) => _curatorService.GetCuratorNameByStudentId(studentId);
    public void AssignCuratorToGroup(int curatorId, int groupId) => _curatorService.AssignToGroup(curatorId, groupId);
}
