package java_hashmap;

public class Estudiante {
    int studentId;
    String fullName;
    String career;
    int semester;
    double gpa;
    int skillScore;

    public Estudiante(int studentId, String fullName, String career, int semester, double gpa, int skillScore) {
        this.studentId = studentId;
        this.fullName = fullName;
        this.career = career;
        this.semester = semester;
        this.gpa = gpa;
        this.skillScore = skillScore;
    }

    @Override
    public String toString() {
        return "ID:          " + studentId + "\n" +
                "Nombre:      " + fullName + "\n" +
                "Carrera:     " + career + "\n" +
                "Semestre:    " + semester + "\n" +
                "GPA:         " + gpa + "\n" +
                "Skill Score: " + skillScore;
    }
}